# -*- Mode:python; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
#
# Copyright (C) 2015-2018 Regents of the University of California.
# Author: Jeff Thompson <jefft0@remap.ucla.edu>
# Author: From ndn-group-encrypt src/group-manager-db https://github.com/named-data/ndn-group-encrypt
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# A copy of the GNU Lesser General Public License is in the file COPYING.

"""
This module defines the Sqlite3GroupManagerDb class which extends GroupManagerDb
to implement the storage of data used by the GroupManager using SQLite.
Note: This class is an experimental feature. The API may change.
"""

import sqlite3
from pyndn.name import Name
from pyndn.util.blob import Blob
from pyndn.encoding.tlv_wire_format import TlvWireFormat
from pyndn.encrypt.schedule import Schedule
from pyndn.encrypt.group_manager_db import GroupManagerDb

INITIALIZATION1 = """
CREATE TABLE IF NOT EXISTS
  schedules(
    schedule_id         INTEGER PRIMARY KEY,
    schedule_name       TEXT NOT NULL,
    schedule            BLOB NOT NULL
  );"""
INITIALIZATION2 = """
CREATE UNIQUE INDEX IF NOT EXISTS
   scheduleNameIndex ON schedules(schedule_name);"""

INITIALIZATION3 = """
CREATE TABLE IF NOT EXISTS
  members(
    member_id           INTEGER PRIMARY KEY,
    schedule_id         INTEGER NOT NULL,
    member_name         BLOB NOT NULL,
    key_name            BLOB NOT NULL,
    pubkey              BLOB NOT NULL,
    FOREIGN KEY(schedule_id)
      REFERENCES schedules(schedule_id)
      ON DELETE CASCADE
      ON UPDATE CASCADE
  );"""
INITIALIZATION4 = """
CREATE UNIQUE INDEX IF NOT EXISTS
   memNameIndex ON members(member_name);"""
INITIALIZATION5 = """
CREATE TABLE IF NOT EXISTS
  ekeys(
    ekey_id             INTEGER PRIMARY KEY,
    ekey_name           BLOB NOT NULL,
    pub_key             BLOB NOT NULL
  );"""
INITIALIZATION6 = """
CREATE UNIQUE INDEX IF NOT EXISTS
   ekeyNameIndex ON ekeys(ekey_name);"""

class Sqlite3GroupManagerDb(GroupManagerDb):
    """
    Create an Sqlite3GroupManagerDb to use the given SQLite3 file.

    :param str databaseFilePath: The path of the SQLite file.
    """
    def __init__(self, databaseFilePath):
        super(Sqlite3GroupManagerDb, self).__init__()

        self._database = sqlite3.connect(databaseFilePath)
        # Key: Name. Value: The encoded private key Blob.
        self._privateKeyBase = {}

        cursor = self._database.cursor()
        # Enable foreign keys.
        cursor.execute("PRAGMA foreign_keys = ON")
        cursor.execute(INITIALIZATION1)
        cursor.execute(INITIALIZATION2)
        cursor.execute(INITIALIZATION3)
        cursor.execute(INITIALIZATION4)
        cursor.execute(INITIALIZATION5)
        cursor.execute(INITIALIZATION6)
        self._database.commit()
        cursor.close()

    #################################################### Schedule management.

    def hasSchedule(self, name):
        """
        Check if there is a schedule with the given name.

        :param str name: The name of the schedule.
        :return: True if there is a schedule.
        :rtype: bool
        :raises GroupManagerDb.Error: For a database error.
        """
        result = False

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT schedule_id FROM schedules where schedule_name=?", (name, ))
            if cursor.fetchone() != None:
                result = True

            cursor.close()
            return result
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.hasSchedule: SQLite error: " + str(ex))

    def listAllScheduleNames(self):
        """
        List all the names of the schedules.

        :return: A new List of String with the names of all schedules.
        :rtype: Array<str>
        :raises GroupManagerDb.Error: For a database error.
        """
        list = []

        try:
            cursor = self._database.cursor()
            cursor.execute("SELECT schedule_name FROM schedules", ())
            results = cursor.fetchall()
            for (name, ) in results:
                list.append(name)
            cursor.close()

            return list
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.listAllScheduleNames: SQLite error: " + str(ex))

    def getSchedule(self, name):
        """
        Get a schedule with the given name.

        :param str name: The name of the schedule.
        :return: A new Schedule object.
        :rtype: Schedule
        :raises GroupManagerDb.Error: If the schedule does not exist or other
          database error.
        """
        schedule = None

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT schedule FROM schedules WHERE schedule_name=?", (name, ))
            result = cursor.fetchone()
            if result != None:
                schedule = Schedule()
                schedule.wireDecode(bytearray(result[0]))
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.getSchedule: SQLite error: " + str(ex))

        if schedule == None:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.getSchedule: Cannot get the result from the database")

        return schedule

    def getScheduleMembers(self, name):
        """
        For each member using the given schedule, get the name and public key
        DER of the member's key.

        :param str name: The name of the schedule.
        :return: a new dictionary where the dictionary's key is the Name of the
          public key and the value is the Blob of the public key DER. Note that
          the member's identity name is keyName.getPrefix(-1). If the schedule
          name is not found, the dictionary is empty.
        :rtype: dictionary<Name, Blob>
        :raises GroupManagerDb.Error: For a database error.
        """
        dictionary = {}

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT key_name, pubkey " +
              "FROM members JOIN schedules ON members.schedule_id=schedules.schedule_id " +
              "WHERE schedule_name=?",
              (name, ))
            results = cursor.fetchall()
            for (keyNameEncoding, keyEncoding) in results:
                keyName = Name()
                keyName.wireDecode(bytearray(keyNameEncoding), TlvWireFormat.get())
                dictionary[keyName] = Blob(bytearray(keyEncoding), False)
            cursor.close()

            return dictionary
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.getScheduleMembers: SQLite error: " + str(ex))

    def addSchedule(self, name, schedule):
        """
        Add a schedule with the given name.

        :param str name: The name of the schedule. The name cannot be empty.
        :param Schedule schedule: The Schedule to add.
        :raises GroupManagerDb.Error: If a schedule with the same name already
          exists, if the name is empty, or other database error.
        """
        if len(name) == 0:
            raise GroupManagerDb.Error(
              "addSchedule: The schedule name cannot be empty")

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "INSERT INTO schedules (schedule_name, schedule) values (?, ?)",
              (name,
               sqlite3.Binary(bytearray(schedule.wireEncode().buf()))))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.addSchedule: SQLite error: " + str(ex))

    def deleteSchedule(self, name):
        """
        Delete the schedule with the given name. Also delete members which use
        this schedule. If there is no schedule with the name, then do nothing.

        :param str name: The name of the schedule.
        :raises GroupManagerDb.Error: For a database error.
        """
        try:
            cursor = self._database.cursor()
            cursor.execute(
              "DELETE FROM schedules WHERE schedule_name=?", (name, ))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.deleteSchedule: SQLite error: " + str(ex))

    def renameSchedule(self, oldName, newName):
        """
        Rename a schedule with oldName to newName.

        :param str oldName: The name of the schedule to be renamed.
        :param str newName: The new name of the schedule. The name cannot be
          empty.
        :raises GroupManagerDb.Error: If a schedule with newName already exists,
          if the schedule with oldName does not exist, if newName is empty, or
          other database error.
        """
        if len(newName) == 0:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.renameSchedule: The schedule newName cannot be empty")

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "UPDATE schedules SET schedule_name=? WHERE schedule_name=?",
              (newName, oldName))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.renameSchedule: SQLite error: " + str(ex))

    def updateSchedule(self, name, schedule):
        """
        Update the schedule with name and replace the old object with the given
        schedule. Otherwise, if no schedule with name exists, a new schedule
        with name and the given schedule will be added to database.

        :param str name: The name of the schedule. The name cannot be empty.
        :param Schedule schedule: The Schedule to update or add.
        :raises GroupManagerDb.Error: If the name is empty, or other database
          error.
        """
        if not self.hasSchedule(name):
            self.addSchedule(name, schedule)
            return

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "UPDATE schedules SET schedule=? WHERE schedule_name=?",
              (sqlite3.Binary(bytearray(schedule.wireEncode().buf())),
               name))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.updateSchedule: SQLite error: " + str(ex))

    #################################################### Member management.

    def hasMember(self, identity):
        """
        Check if there is a member with the given identity name.

        :param Name identity: The member's identity name.
        :return: True if there is a member.
        :rtype: bool
        :raises GroupManagerDb.Error: For a database error.
        """
        result = False

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT member_id FROM members WHERE member_name=?",
              (sqlite3.Binary(bytearray(identity.wireEncode(TlvWireFormat.get()).buf())), ))
            if cursor.fetchone() != None:
                result = True

            cursor.close()
            return result
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.hasMember: SQLite error: " + str(ex))

    def listAllMembers(self):
        """
        List all the members.

        :return: A new List of Name with the names of all members.
        :rtype: Array<Name>
        :raises GroupManagerDb.Error: For a database error.
        """
        list = []

        try:
            cursor = self._database.cursor()
            cursor.execute("SELECT member_name FROM members", ())
            results = cursor.fetchall()
            for (nameEncoding, ) in results:
                identity = Name()
                identity.wireDecode(bytearray(nameEncoding), TlvWireFormat.get())
                list.append(identity)
            cursor.close()

            return list
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.listAllMembers: SQLite error: " + str(ex))

    def getMemberSchedule(self, identity):
        """
        Get the name of the schedule for the given member's identity name.

        :param Name identity: The member's identity name.
        :return: The name of the schedule.
        :rtype: str
        :raises GroupManagerDb.Error: If there's no member with the given
          identity name in the database, or other database error.
        """
        scheduleName = None

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT schedule_name " +
              "FROM schedules JOIN members ON schedules.schedule_id = members.schedule_id " +
              "WHERE member_name=?",
              (sqlite3.Binary(bytearray(identity.wireEncode(TlvWireFormat.get()).buf())), ))
            result = cursor.fetchone()
            if result != None:
                scheduleName = result[0]
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.getMemberSchedule: SQLite error: " + str(ex))

        if scheduleName == None:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.getMemberSchedule: Cannot get the result from the database")

        return scheduleName

    def addMember(self, scheduleName, keyName, key):
        """
        Add a new member with the given key named keyName into a schedule named
        scheduleName. The member's identity name is keyName.getPrefix(-1).

        :param str scheduleName: The schedule name.
        :param Name keyName: The name of the key.
        :param Blob key: A Blob of the public key DER.
        :raises GroupManagerDb.Error: If there's no schedule named scheduleName,
          if the member's identity name already exists, or other database error.
        """
        scheduleId = self._getScheduleId(scheduleName)
        if scheduleId == -1:
          raise GroupManagerDb.Error("The schedule does not exist")

        # Needs to be changed in the future.
        memberName = keyName.getPrefix(-1)

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "INSERT INTO members(schedule_id, member_name, key_name, pubkey) " +
                "values (?, ?, ?, ?)",
              (scheduleId,
               sqlite3.Binary(bytearray(memberName.wireEncode(TlvWireFormat.get()).buf())),
               sqlite3.Binary(bytearray(keyName.wireEncode(TlvWireFormat.get()).buf())),
               sqlite3.Binary(bytearray(key.buf()))))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.addMember: SQLite error: " + str(ex))

    def updateMemberSchedule(self, identity, scheduleName):
        """
        Change the name of the schedule for the given member's identity name.

        :param Name identity: The member's identity name.
        :param str scheduleName: The new schedule name.
        :raises GroupManagerDb.Error: If there's no member with the given
          identity name in the database, or there's no schedule named
          scheduleName, or other database error.
        """
        scheduleId = self._getScheduleId(scheduleName)
        if scheduleId == -1:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.updateMemberSchedule: The schedule does not exist");

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "UPDATE members SET schedule_id=? WHERE member_name=?",
              (scheduleId,
               sqlite3.Binary(bytearray(identity.wireEncode(TlvWireFormat.get()).buf()))))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.updateMemberSchedule: SQLite error: " + str(ex))

    def deleteMember(self, identity):
        """
        Delete a member with the given identity name. If there is no member with
        the identity name, then do nothing.

        :param Name identity: The member's identity name.
        :raises GroupManagerDb.Error: For a database error.
        """
        try:
            cursor = self._database.cursor()
            cursor.execute(
              "DELETE FROM members WHERE member_name=?",
              (sqlite3.Binary(bytearray(identity.wireEncode(TlvWireFormat.get()).buf())), ))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.deleteMember: SQLite error: " + str(ex))

    def hasEKey(self, eKeyName):
        """
        Check if there is an EKey with the name eKeyName in the database.

        :param Name eKeyName: The name of the EKey.
        :return: True if the EKey exists.
        :rtype: bool
        :raises GroupManagerDb.Error: For a database error.
        """
        result = False

        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT ekey_id FROM ekeys where ekey_name=?",
              (sqlite3.Binary(bytearray(eKeyName.wireEncode(TlvWireFormat.get()).buf())), ))
            if cursor.fetchone() != None:
                result = True

            cursor.close()
            return result
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.hasEKey: SQLite error: " + str(ex))

    def addEKey(self, eKeyName, publicKey, privateKey):
        """
        Add the EKey with name eKeyName to the database.

        :param Name eKeyName: The name of the EKey. This copies the Name.
        :param Blob publicKey: The encoded public key of the group key pair.
        :param Blob privateKey: The encoded private key of the group key pair.
        :raises GroupManagerDb.Error: If a key with name eKeyName already exists
          in the database, or other database error.
        """
        try:
            cursor = self._database.cursor()
            cursor.execute(
              "INSERT INTO ekeys(ekey_name, pub_key) values (?, ?)",
              (sqlite3.Binary(bytearray(eKeyName.wireEncode(TlvWireFormat.get()).buf())),
               sqlite3.Binary(bytearray(publicKey.buf()))))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.addEKey: SQLite error: " + str(ex))

        self._privateKeyBase[Name(eKeyName)] = privateKey

    def getEKey(self, eKeyName):
        """
        Get the group key pair with the name eKeyName from the database.

        :param Name eKeyName: The name of the EKey.
        :return: A tuple (privateKeyBlob, publicKeyBlob) where "privateKeyBlob"
          is the encoding Blob of the private key and "publicKeyBlob" is the
          encoding Blob of the public key.
        :rtype: (Blob, Blob)
        :raises GroupManagerDb.Error: If the key with name eKeyName does not
          exist in the database, or other database error.
        """
        publicKey = None
        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT pub_key FROM ekeys where ekey_name=?",
              (sqlite3.Binary(bytearray(eKeyName.wireEncode(TlvWireFormat.get()).buf())), ))
            result = cursor.fetchone()
            if result != None:
                publicKey = Blob(bytearray(result[0]), False)
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.getMemberSchedule: SQLite error: " + str(ex))

        if publicKey == None:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.getEKey: Cannot get the result from the database")

        return (publicKey, self._privateKeyBase[Name(eKeyName)])

    def cleanEKeys(self):
        """
        Delete all the EKeys in the database. The database will keep growing
        because EKeys will keep being added, so this method should be called
        periodically.

        :raises GroupManagerDb.Error: For a database error.
        """
        try:
            cursor = self._database.cursor()
            cursor.execute("DELETE FROM ekeys", (None,))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.cleanEKeys: SQLite error: " + str(ex))

        self._privateKeyBase = {}

    def deleteEKey(self, eKeyName):
        """
        Delete the EKey with name eKeyName from the database. If no key with the
        name exists in the database, do nothing.

        :param Name eKeyName: The name of the EKey.
        :raises GroupManagerDb.Error: For a database error.
        """
        try:
            cursor = self._database.cursor()
            cursor.execute(
              "DELETE FROM ekeys WHERE ekey_name=?",
              (sqlite3.Binary(bytearray(eKeyName.wireEncode(TlvWireFormat.get()).buf())), ))
            self._database.commit()
            cursor.close()
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb.deleteEKey: SQLite error: " + str(ex))

        del self._privateKeyBase[eKeyName]

    def _getScheduleId(self, name):
        """
        Get the ID for the schedule.

        :param str name: The schedule name.
        :return: The ID, or -1 if the schedule name is not found.
        :rtype: int
        :raises GroupManagerDb.Error: For a database error.
        """
        try:
            cursor = self._database.cursor()
            cursor.execute(
              "SELECT schedule_id FROM schedules WHERE schedule_name=?", (name, ))
            result = cursor.fetchone()
            id = -1
            if result != None:
                return result[0]
            cursor.close()

            return id
        except Exception as ex:
            raise GroupManagerDb.Error(
              "Sqlite3GroupManagerDb._getScheduleId: SQLite error: " + str(ex))
