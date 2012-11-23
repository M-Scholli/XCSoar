/* Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2012 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "Time/RoughTime.hpp"
#include "TestUtil.hpp"

int main(int argc, char **argv)
{
  plan_tests(39);

  RoughTime a = RoughTime::Invalid();
  ok1(!a.IsValid());

  a = RoughTime(12, 1);
  ok1(a.IsValid());
  ok1(a.GetHour() == 12);
  ok1(a.GetMinute() == 1);
  ok1(a.GetMinuteOfDay() == 12 * 60 + 1);

  /* compare a RoughTime with itself */
  ok1(a == a);
  ok1(!(a != a));
  ok1(a <= a);
  ok1(a >= a);
  ok1(!(a < a));
  ok1(!(a > a));

  /* compare a RoughTime with another one */
  RoughTime b(11, 59);
  ok1(b.IsValid());
  ok1(a != b);
  ok1(!(a == b));
  ok1(!(a <= b));
  ok1(a >= b);
  ok1(!(a < b));
  ok1(a > b);
  ok1(b != a);
  ok1(!(b == a));
  ok1(b <= a);
  ok1(!(b >= a));
  ok1(b < a);
  ok1(!(b > a));

  /* test RoughTimeSpan::IsInside() */
  RoughTimeSpan s = RoughTimeSpan::Invalid();
  ok1(!s.IsDefined());
  ok1(s.IsInside(a));
  ok1(s.IsInside(b));

  s = RoughTimeSpan(RoughTime(12, 0), RoughTime::Invalid());
  ok1(s.IsDefined());
  ok1(s.IsInside(a));
  ok1(!s.IsInside(b));

  s = RoughTimeSpan(RoughTime::Invalid(), RoughTime(12, 0));
  ok1(s.IsDefined());
  ok1(!s.IsInside(a));
  ok1(s.IsInside(b));

  s = RoughTimeSpan(RoughTime(12, 0), RoughTime(12, 1));
  ok1(s.IsDefined());
  ok1(!s.IsInside(a));
  ok1(!s.IsInside(b));

  s = RoughTimeSpan(RoughTime(12, 0), RoughTime(12, 30));
  ok1(s.IsDefined());
  ok1(s.IsInside(a));
  ok1(!s.IsInside(b));

  return exit_status();
}
