# Description
ArduConfigFile is a arduino lib to process config files from SD card with format:
<pre>
[Section1]
bool=true
[Section 2]
bool=on
string=str
int=int
</pre>

# Note
This function use "readStringUntil" for read the value after '='

# Licencia
ArduConfigFile
Copyright (C) 2017  Victor Torre

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

