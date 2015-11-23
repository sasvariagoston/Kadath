// Copyright (C) 2014 - 2015 Ágoston Sasvári
// All rights reserved.
// This code is published under the GNU Lesser General Public License.

#ifndef SETTINGS_KADATH_HPP_
#define SETTINGS_KADATH_HPP_

#include <limits>
#include <string>

using namespace std;

namespace {

const string BS = "/";
const string LST = "kadath.lst";
const string ICON_FLDR = "icon";
const string TLST = "tidy.lst";
const string FLOC = "fenykepek";
const string ITAG = "_icon.jpg";
const string ILOC = FLOC + BS + ICON_FLDR;

}

inline double NaN() { return numeric_limits<double>::quiet_NaN(); }

string return_LIST_HEAD ();

string return_ELEMENT_properties_element_font_color ();

string return_ELEMENT_properties_font_color ();

#endif /* SETTINGS_KADATH_HPP_ */
