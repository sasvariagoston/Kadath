
// Copyright (C) 2014 - 2015 Ágoston Sasvári
// All rights reserved.
// This code is published under the GNU Lesser General Public License.

#ifndef GENERATE_HTML_HPP_
#define GENERATE_HTML_HPP_

#include <fstream>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "struct.hpp"

void generate_html_head (ofstream& o, const vector <ICON>& IC, const size_t i, const string MODE);

void tracking_code (ofstream& o);

void body_style (ofstream& o, const string MODE);

vector <size_t> set_cells_geometry_4_element (const size_t N);

void dump_IMAGE (ofstream& o, const vector <ICON>& I, const size_t IMAGE_COUNTER);

void dump_LINK (ofstream& o, const vector <ICON>& I, const size_t LINK_COUNTER);

void generate_main_table (ofstream& o, const vector <ICON>& I, const vector <size_t> CELL_GEOM);

void generate_pictures_table (ofstream& o, const vector <ICON>& IC);

vector <ICON> return_index_links ();

void generate_index_table_menupoint (ofstream& o, const size_t THIS, const string WIDTH);

void generate_index_table (ofstream& o);

string return_filename (const vector <ICON>& IC, const size_t i, const string MODE);

void generate_elements_table (ofstream& o, const vector <ICON>& IC, const size_t i);

void generate_interviews (ofstream& o);

void generate_publications (ofstream& o);

void generate_html (const vector <ICON>& IC, const size_t i, const string MODE);

void cout_html (const vector <ICON>& I);

#endif /* GENERATE_HTML_HPP_ */
