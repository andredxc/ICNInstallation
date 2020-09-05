/**
 * Copyright (C) 2013-2018 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * A copy of the GNU Lesser General Public License is in the file COPYING.
 */

package net.named_data.jndn;
import net.named_data.jndn.util.Blob;
import net.named_data.jndn.util.ChangeCountable;

/**
 * A Signature is an abstract base class providing methods to work with the
 * signature information in a Data packet.
 * You must create an object of a subclass, for example Sha256WithRsaSignature.
 */
public abstract class Signature implements ChangeCountable {
  /**
   * Return a new Signature which is a deep copy of this signature.
   * This is abstract, the subclass must implement it.
   * @return A new Sha256WithRsaSignature.
   * @throws CloneNotSupportedException
   */
  public abstract Object clone() throws CloneNotSupportedException;

  /**
   * Get the signature bytes.
   * @return The signature bytes. If not specified, the value isNull().
   */
  public abstract Blob
  getSignature();

  /**
   * Set the signature bytes to the given value.
   * @param signature A Blob with the signature bytes.
   */
  public abstract void
  setSignature(Blob signature);

  /**
   * Get the change count, which is incremented each time this object
   * (or a child object) is changed.
   * @return The change count.
   */
  public abstract long getChangeCount();
}
