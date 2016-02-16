////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2006 - 2016, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#include <cmake.h>
#include <Duration.h>

////////////////////////////////////////////////////////////////////////////////
Duration::Duration ()
{
  clear ();
}

////////////////////////////////////////////////////////////////////////////////
Duration::Duration (const std::string& input)
{
  clear ();
  std::string::size_type idx = 0;
  parse (input, idx);
}

////////////////////////////////////////////////////////////////////////////////
Duration::Duration (time_t input)
{
  clear ();
  _period = input;
}

////////////////////////////////////////////////////////////////////////////////
bool Duration::operator< (const Duration& other)
{
  return _period < other._period;
}

////////////////////////////////////////////////////////////////////////////////
bool Duration::operator> (const Duration& other)
{
  return _period > other._period;
}

////////////////////////////////////////////////////////////////////////////////
std::string Duration::toString () const
{
  std::stringstream s;
  s << _period;
  return s.str ();
}

////////////////////////////////////////////////////////////////////////////////
time_t Duration::toTime_t () const
{
  return _period;
}

////////////////////////////////////////////////////////////////////////////////
bool Duration::parse (const std::string& input, std::string::size_type& start)
{
  auto i = start;
  Pig pig (input);
  if (i)
    pig.skipN (static_cast <int> (i));

  if (parse_seconds (pig))
  {
    // ::validate and ::resolve are not needed in this case.
    start = pig.cursor ();
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
bool Duration::parse_seconds (Pig& pig)
{
  auto checkpoint = pig.cursor ();

  pig.restoreTo (checkpoint);
  return false;
}

////////////////////////////////////////////////////////////////////////////////
void Duration::clear ()
{
  _year    = 0;
  _month   = 0;
  _day     = 0;
  _hours   = 0;
  _minutes = 0;
  _seconds = 0;
  _period  = 0;
}

////////////////////////////////////////////////////////////////////////////////
// Allow un-normalized values.
void Duration::resolve ()
{
  _period = (_year  * 365 * 86400) +
            (_month  * 30 * 86400) +
            (_day         * 86400) +
            (_hours       *  3600) +
            (_minutes     *    60) +
            _seconds;
}

////////////////////////////////////////////////////////////////////////////////
/*
std::string Duration::dump () const
{
  std::stringstream s;
  s << "Duration"
    << " y"  << _year
    << " mo" << _month
    << " d"  << _day
    << " h"  << _hours
    << " mi" << _minutes
    << " s"  << _seconds
    << " ="  << _period
    << "  "  << (_period ? format () : "");

  return s.str ();
}
*/

////////////////////////////////////////////////////////////////////////////////
