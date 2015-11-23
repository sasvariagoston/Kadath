
// Copyright (C) 2014 - 2015 Ágoston Sasvári
// All rights reserved.
// This code is published under the GNU Lesser General Public License.

#include "generate_html.hpp"
#include "css_html_formatting.cpp"
#include "utils.hpp"

using namespace std;

void generate_html_head (ofstream& o, const vector <ICON>& IC, const size_t i, const string MODE) {

	const bool E = MODE == "ELEMENT";

	html_open (o);
	head_open (o);
	meta_open(o, "");
	charset (o, "utf-8");
	tag_end(o);

	if (!E) title (o, "KADATH", "");
	else title (o, IC.at(i).TITLE, "");

	string PATH = "";
	if (E) PATH = "../../";

	const string ICONNAME = PATH + "icon.ico";

	icon (o, ICONNAME);
	head_close (o);
}

void tracking_code (ofstream& o) {

	o << "<script type="<<T<<"text/javascript"<<T<<">" << endl;
	o << "  var _gaq = _gaq || [];" << endl;
	o << "  _gaq.push(['_setAccount', 'UA-3957310-1']);" << endl;
	o << "  _gaq.push(['_setDomainName', 'kadath.hu']);" << endl;
	o << "  _gaq.push(['_trackPageview']);" << endl;
	o << "  (function() {" << endl;
	o << "    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;" << endl;
	o << "    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';" << endl;
	o << "    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);" << endl;
	o << "  })();" << endl;
	o << "</script>" << endl;
}

void body_style (ofstream& o, const string MODE) {

	const bool I = MODE == "INDEX";
	const bool E = MODE == "ELEMENT";
	const bool B = MODE == "PUBLICATIONS";
	const bool W = MODE == "INTERVIEWS";

	string PATH = "";
	if (E) PATH = "../../";

	body_open (o);
	style_open (o);
	style_text_align(o, "center");
	style_background_color (o, "0, 0, 0");

	if (I) style_background_image (o, PATH + "02.jpg");
	else if (E || B || W) style_background_image (o, PATH + "04.jpg");
	else style_background_image (o, PATH + "03.jpg");

	style_background_repeat (o, "no-repeat");
	style_background_position(o, "center top");
	style_background_attachment (o, "fixed");
	style_background_size (o, "100%");
	style_close (o);
	tag_end (o);
}

vector <size_t> set_cells_geometry_4_element (const size_t N) {

	vector <size_t> OUT;

	for (size_t i = 4; i < N; i+=4) OUT.push_back (4);

	OUT.push_back (4);

	return OUT;
}

void dump_IMAGE (ofstream& o, const vector <ICON>& I, const size_t IMAGE_COUNTER) {

	cell_open(o);
	tag_end(o);

	link_start (o);
	link_target (o, I.at(IMAGE_COUNTER).TARGET);
	link_href (o, I.at(IMAGE_COUNTER).HREF);
	image_open(o, I.at(IMAGE_COUNTER).ICON_FILENAME);
	style_open(o);
	style_width (o, "200px");
	style_height(o, "133px");
	style_close(o);
	tag_end(o);

	cell_close(o);
}

void dump_LINK (ofstream& o, const vector <ICON>& I, const size_t LINK_COUNTER) {

	cell_open(o);

	style_open(o);
	style_width (o, "200px");
	style_height(o, "20px");
	style_text_align(o, "center");
	style_vertical_align (o, "middle");
	style_close(o);
	tag_end(o);

	link_start (o);
	style_open(o);

	style_text_color (o, I.at(LINK_COUNTER).COLOR);
	style_font_family (o, I.at(LINK_COUNTER).FACE);
	style_font_size(o, I.at(LINK_COUNTER).SIZE);
	style_text_decoration (o, "none");
	style_font_weight(o, "bold");
	style_close(o);
	link_target (o, I.at(LINK_COUNTER).TARGET);
	link_href (o, I.at(LINK_COUNTER).HREF);

	link_title (o, I.at(LINK_COUNTER).LINKTEXT);

	link_end (o);
	cell_close(o);
}

void generate_main_table (ofstream& o, const vector <ICON>& I, const vector <size_t> CELL_GEOM) {

	size_t IMAGE_COUNTER = 0;
	size_t LINK_COUNTER = 0;
	const size_t MAX = I.size();

	table_open (o, "center");
	tag_end(o);

	for (size_t i = 0; i < CELL_GEOM.size(); i++) {

		row_open(o);
		style_open(o);
		style_width (o, "804px");
		style_height(o, "133px");
		style_close(o);
		tag_end(o);

		for (size_t j = 0; j < 4; j++) {

			const bool EMPTY = IMAGE_COUNTER > MAX - 1;

			if (!EMPTY) dump_IMAGE (o, I, IMAGE_COUNTER);

			IMAGE_COUNTER++;
		}
		row_close(o);

		row_open(o);
		style_open(o);
		style_width (o, "804px");
		style_height(o, "20px");
		style_close(o);
		tag_end(o);
		for (size_t j = 0; j < 4; j++) {

			const bool EMPTY = LINK_COUNTER > MAX - 1;

			if (!EMPTY) dump_LINK (o, I, LINK_COUNTER);

			LINK_COUNTER++;
		}
		row_close(o);
	}
	table_close(o);
}

void generate_pictures_table (ofstream& o, const vector <ICON>& IC) {

	vector <size_t> CELL_GEOM = set_cells_geometry_4_element (IC.size());

	generate_main_table (o, IC, CELL_GEOM);
}

vector <ICON> return_index_links () {

	vector <ICON> OUT;

	ICON buf;

	buf.TARGET = "_self";
	buf.HREF = "publications.htm";
	buf.TITLE = "[ PUBLICATIONS ]";
	OUT.push_back (buf);

	buf.TARGET = "_self";
	buf.HREF = "pictures.htm";
	buf.TITLE = "[ PICTURES ]";
	OUT.push_back (buf);

	buf.TARGET = "_self";
	buf.HREF = "www.sg2ps.eu";
	buf.TITLE = "[ SG2PS ]";
	OUT.push_back (buf);

	buf.TARGET = "_self";
	buf.HREF = "interviews_reviews.htm";
	buf.TITLE = "[ INTERVIEWS, REVIEWS ]";
	OUT.push_back (buf);


	return OUT;
}

void generate_index_table_menupoint (ofstream& o, const size_t THIS, const string WIDTH) {

	vector <ICON> L = return_index_links ();

	cell_open(o);
	style_open(o);
	style_width(o, WIDTH);
	style_close(o);
	tag_end(o);

	link_start (o);
	style_open(o);
	style_text_color (o, "255, 255, 255");
	style_font_family (o, "Verdana");
	style_font_size(o, "14");
	style_font_weight(o, "bold");
	style_text_decoration (o, "none");
	style_close(o);
	link_target (o, L.at(THIS).TARGET);
	link_href (o, L.at(THIS).HREF);
	link_title (o, L.at(THIS).TITLE);
	link_end (o);
	cell_close(o);
}

void generate_index_table (ofstream& o) {

	table_open(o, "center");
	style_open(o);
	style_text_align(o, "center");
	style_width(o, "100%");
	style_height (o, "70%");
	style_close(o);
	tag_end(o);

	row_open(o);
	style_open(o);
	style_width(o, "100%");
	//style_height (o, "100%");
	style_close(o);
	tag_end(o);
	row_close(o);
	table_close(o);

	table_open(o, "center");
	style_open(o);
	style_text_align(o, "center");
	style_width(o, "100%");
	style_height (o, "15%");
	style_close(o);
	tag_end(o);

	row_open(o);
	style_open(o);
	style_width(o, "100%");
	//style_height (o, "100%");
	style_close(o);
	tag_end(o);
	generate_index_table_menupoint (o, 1, "100%");
	row_close(o);
	table_close(o);

	table_open(o, "center");
	style_open(o);
	style_text_align(o, "center");
	style_width(o, "100%");
	style_height (o, "15%");
	style_close(o);
	tag_end(o);

	row_open(o);
	style_open(o);
	style_width(o, "100%");
	//style_height (o, "100%");
	style_close(o);
	tag_end(o);
	generate_index_table_menupoint (o, 0, "33%");
	generate_index_table_menupoint (o, 2, "33%");
	generate_index_table_menupoint (o, 3, "33%");
	row_close(o);
	table_close(o);
}

string return_filename (const vector <ICON>& IC, const size_t i, const string MODE) {

	const bool P = MODE == "PICTURES";
	const bool I = MODE == "INDEX";
	const bool B = MODE == "PUBLICATIONS";
	const bool W = MODE == "INTERVIEWS";

	if (I) return "index.htm";
	else if (P) return "pictures.htm";
	else if (B) return "publications.htm";
	else if (W) return "interviews_reviews.htm";
	else return IC.at(i).HREF;
}

void generate_elements_table (ofstream& o, const vector <ICON>& IC, const size_t i) {

	const size_t FN = IC.at(i).FILE_NUMBER;
	const string ON = IC.at(i).ORIGINAL_NAME;

	size_t COUNTER = 1;

	for (size_t j = 1; j < FN; j+=2) {

		string LT10 = "";
		if (COUNTER < 10) LT10 = "0";

		string LT100 = "";
		if (COUNTER < 100) LT100 = "0";

		ostringstream os;
		os << LT10 << LT100 << COUNTER << flush;

		const string JPG  = ON + "_" + os.str() + ".jpg";
		const string TJPG = ON + "_" + os.str() + "_th.jpg";

		link_start(o);
		style_open(o);
		style_close(o);
		link_target(o, "_blank");
		link_href(o, JPG);

		image_open(o, TJPG);
		style_open(o);
		style_close(o);
		tag_end(o);
		link_end(o);

		linebreak(o);
		linebreak(o);

		o << endl;

		COUNTER++;
	}
}

void generate_interviews (ofstream& o) {

	vector <string> P = read_text_file ("interviews_reviews.txt");

	if (P.size() == 0) return;

	table_open(o, "center");
	style_open(o);
	style_width(o, "100%");
	style_close(o);
	tag_end(o);

	cell_open(o);
	tag_end(o);
	cell_close(o);

	cell_open(o);
	style_open(o);
	style_width(o, "700px");
	style_text_color(o, "255, 255, 255");
	style_close(o);
	tag_end(o);

	for (size_t i = 0; i < P.size(); i++) {

		write (o, P.at(i), "Verdana", "14", "justify", "150%");
	}

	cell_close(o);

	cell_open(o);
	tag_end(o);
	cell_close(o);

	table_close(o);
}

void generate_publications (ofstream& o) {

	vector <string> P = read_text_file ("publications.txt");

	if (P.size() == 0) return;

	table_open(o, "center");
	style_open(o);
	style_width(o, "100%");
	style_close(o);
	tag_end(o);

	cell_open(o);
	tag_end(o);
	cell_close(o);

	cell_open(o);
	style_open(o);
	style_width(o, "700px");
	style_text_color(o, "255, 255, 255");
	style_close(o);
	tag_end(o);

	/*

	 *******        FUNCTION WRITE        ********

		 ~ TEXT ~         -> italic
		 * TEXT *         -> bold
		 # TEXT #         -> insert image
		 { LINK {} TEXT } -> TEXT, pointing to LINK

	*/

	for (size_t i = 0; i < P.size(); i++) {

		write (o, P.at(i), "Verdana", "14", "justify", "150%");
	}

	cell_close(o);

	cell_open(o);
	tag_end(o);
	cell_close(o);

	table_close(o);
}

void generate_html (const vector <ICON>& IC, const size_t i, const string MODE) {

	const bool P = MODE == "PICTURES";
	const bool B = MODE == "PUBLICATIONS";
	const bool I = MODE == "INDEX";
	const bool E = MODE == "ELEMENT";
	const bool W = MODE == "INTERVIEWS";

	string FILENAME = return_filename (IC, i, MODE);

	cout << "    Creating '" << FILENAME << "' file..." << endl;

	ofstream o;
	o.open (FILENAME.c_str());

	generate_html_head (o, IC, i, MODE);
	tracking_code (o);
	body_style (o, MODE);

	if (P) generate_pictures_table (o, IC);

	if (I) generate_index_table (o);

	if (E) generate_elements_table (o, IC, i);

	if (B) generate_publications (o);

	if (W) generate_interviews (o);

	body_close(o);
}

void cout_html (const vector <ICON>& I) {

	generate_html (I, 999, "INDEX");
	generate_html (I, 999, "PICTURES");
	generate_html (I, 999, "PUBLICATIONS");
	generate_html (I, 999, "INTERVIEWS");

	for (size_t i = 0; i < I.size(); i++) {

		generate_html (I, i, "ELEMENT");
	}
}
