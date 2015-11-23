// Copyright (C) 2014 - 2015 Ágoston Sasvári
// All rights reserved.
// This code is published under the GNU Lesser General Public License.

#ifndef KADATH_HPP_
#define KADATH_HPP_

#include <limits>

#include "struct.hpp"

using namespace std;

vector <string> return_FOLDERS_with_order ();

bool check_folders (const vector <string>& N);

bool check_icons (const vector <string>& N);

vector <ICON> generate_ORIGINAL_NAMES (const vector <string>& N);

size_t return_FILE_NUMBER_individual_folder (const ICON& I);

vector <ICON> return_FILE_NUMBER (const vector <ICON>& I);

vector <ICON> generate_YEAR_MONTH (const vector <ICON>& I);

vector <ICON> generate_NAME (const vector <ICON>& I) ;

vector <ICON> generate_HREF (const vector <ICON>& I);

vector <ICON> generate_FACE (const vector <ICON>& I);

vector <ICON> generate_PAGE_NAME (const vector <ICON>& I) ;

vector <ICON> tidy_PAGE_NAME (const vector <ICON>& I);

vector <ICON> generate_ICONNAME (const vector <ICON>& I);

vector <ICON> generate_TITLE (const vector <ICON>& I);

string return_roman_MONTH (const string M) ;

vector <ICON> generate_LINKTEXT (const vector <ICON>& I);

bool by_ID (const ICON& x, const ICON& y);

bool by_rev_ID (const ICON& x, const ICON& y);

vector < vector < vector <ICON> > > generate_ICONMATRIX (const vector <ICON>& I);

void dbg_cout_I (const vector <ICON> & I);

void dbg_cout_I_vvv (const vector < vector < vector <ICON> > >& I_vvv);


#endif /* KADATH_HPP_ */
