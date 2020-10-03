/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

smaucourt@gmail.com - 11/11/2018
*/

#ifndef Yeelight_h
#define Yeelight_h

class Yeelight
{
public:
  Yeelight();
  ~Yeelight();
  void lookup();
  int feedback();
  String getLocation();
  String getSupport();
  bool isPowered();
  String sendCommand(String method, String params);
private:
  void parseFeedback(char* buffer, size_t len);
};

#endif
