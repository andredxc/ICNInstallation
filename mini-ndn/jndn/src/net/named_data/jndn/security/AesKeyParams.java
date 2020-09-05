/**
 * Copyright (C) 2015-2018 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * @author: From code in ndn-cxx by Yingdi Yu <yingdi@cs.ucla.edu>
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

package net.named_data.jndn.security;

import net.named_data.jndn.Name;

public class AesKeyParams extends KeyParams {
  public AesKeyParams(Name.Component keyId, int size)
  {
    super(getType(), keyId);
    size_ = size;
  }

  public AesKeyParams(Name.Component keyId)
  {
    super(getType(), keyId);
    size_ = getDefaultSize();
  }

  public AesKeyParams(int size, KeyIdType keyIdType)
  {
    super(getType(), keyIdType);
    size_ = size;
  }

  public AesKeyParams(int size)
  {
    super(getType(), KeyIdType.RANDOM);
    size_ = size;
  }

  public AesKeyParams()
  {
    super(getType(), KeyIdType.RANDOM);
    size_ = getDefaultSize();
  }

  public int
  getKeySize()
  {
    return size_;
  }

  public static int
  getDefaultSize() { return 64; }

  public static KeyType
  getType() { return KeyType.AES; }

  private final int size_;
}
