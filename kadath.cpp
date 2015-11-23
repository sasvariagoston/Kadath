
// Copyright (C) 2014 - 2015 Ágoston Sasvári
// All rights reserved.
// This code is published under the GNU Lesser General Public License.

#include <algorithm>

#include "generate_html.hpp"
#include "kadath.hpp"
#include "settings.hpp"
#include "settings_kadath.hpp"
#include "struct.hpp"
#include "utils.cpp"

using namespace std;

vector <string> return_FOLDERS_with_order () {

	ifstream L;
	L.open (LST.c_str());

	vector <string> OUT;
	vector <string> TEMP;
	string buf;

	while (getline (L, buf)) TEMP.push_back(buf);

	for (size_t i = 0; i < TEMP.size(); i++) {

		if (TEMP.at(i).size() > 8) {

			OUT.push_back (TEMP.at(i));
			cout << "     Folder '" << TEMP.at(i) << "' read from " << LST << " list file." << endl;
		}
	}

	if (OUT.size() == 0) cout << "!    Error - the '" << LST << "' file is empty" << endl << endl;
	else cout << "     File '" << LST << "' read, and " << OUT.size() << " record were found." << endl << endl;

	return OUT;
}

bool check_folders (const vector <string>& N) {

	size_t error = 0;

	for (size_t i = 0; i < N.size(); i++) {

		const string CMD = "chdir " + FLOC + BS + N.at(i);

		const int RES = system (CMD.c_str());

		if (RES) {

			cout << "!   ERROR - '" + N.at(i) + "' folder doesn't exist." << endl;
			error++;
		}
		else cout << "    OK - '" + N.at(i) + "' folder does exist." << endl;
	}
	cout << endl;

	if (error > 0) {

		cout << "!    FINISHED - error opening " << error << " folders." << endl;
		return false;
	}
	cout << "    FINISHED - each folders are OK." << endl;

	return true;
}

bool check_icons (const vector <string>& N) {

	cout << endl;

	const string CMD = "chdir " + ILOC;

	const int RES = system (CMD.c_str());

	if (RES) {

		cout << "!   ERROR - the '" << ILOC << "' folder doesn't exist." << endl;
		return false;
	}
	else cout << "    OK - the '" << ILOC << "' folder does exist." << endl << endl;

	size_t FLT_ICN = 0;

	for (size_t i = 0; i < N.size(); i++) {

		ifstream ICON;
		string FN = "";
		FN = FN + ILOC + BS + N.at(i) + "_icon.jpg";
		ICON.open (FN.c_str());

		string TEST;

		getline (ICON, TEST);

		ICON.close();

		if (TEST.size() < 1) {

			cout << "!   ERROR - '" + N.at(i) + "_icon.jpg' file doesn't exist." << endl;
			FLT_ICN++;
		}
		else cout << "    OK - '" + N.at(i) + "_icon.jpg' file does exist." << endl;
	}
	if (FLT_ICN > 0) {

		cout << "!   FINISHED - missing " << + FLT_ICN << " icon files." << endl;
		return false;
	}
	cout << "    DONE - each icon files are present." << endl;
	return true;
}

vector <ICON> generate_ORIGINAL_NAMES (const vector <string>& N) {

	vector <ICON> OUT;

	for (size_t i = 0; i < N.size(); i++) {

		ICON buf;

		buf.ORIGINAL_NAME = N.at(i);
		buf.ID = i;

		OUT.push_back (buf);
	}
	return OUT;
}

size_t return_FILE_NUMBER_individual_folder (const ICON& I) {

	size_t OUT = NaN();

	const string FLDR = I.ORIGINAL_NAME;

	const string CMD1 = "dir " + FLOC + "\\" + FLDR + " >> dir.lst";

	int RES = system (CMD1.c_str());

	if (RES) cout << "!   ERROR - cannot read '" + FLDR + "' folder." << endl;
	else {

		vector <string> TEMP;
		string buf;

		ifstream DIRLIST;
		string FN = "dir.lst";
		DIRLIST.open (FN.c_str());

		while (getline (DIRLIST, buf, '\n')) TEMP.push_back (buf);

		OUT = TEMP.size() - 9;

		cout << "    OK - '" + FLDR + "' folder has " << OUT << " files." << endl;

		DIRLIST.close();
	}
	const string CMD2 = "del dir.lst";
	RES = system (CMD2.c_str());

	return OUT;
}

vector <ICON> return_FILE_NUMBER (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		OUT.at(i).FILE_NUMBER = return_FILE_NUMBER_individual_folder (OUT.at(i));
	}
	return OUT;
}

vector <ICON> generate_YEAR_MONTH (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		const string A = I.at(i).ORIGINAL_NAME;

		ostringstream os1;

		os1	<< A.at(0) << A.at(1) << A.at(2) << A.at(3) << flush;

		const string Y = os1.str();

		OUT.at(i).YEAR = Y;

		ostringstream os2;

		os2 << A.at(5) << A.at(6) << flush;

		const string M = os2.str();

		OUT.at(i).MONTH = M;
	}
	return OUT;
}

vector <ICON> generate_NAME (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		const string act_ORIG_NAME = I.at(i).ORIGINAL_NAME;

		ostringstream os;

		for (size_t j = 8; j < act_ORIG_NAME.size(); j++) {

			os << act_ORIG_NAME.at(j) << flush;
		}

		const string N = os.str();

		OUT.at(i).NAME = N;
	}
	return OUT;
}

vector <ICON> generate_HREF (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		const ICON A = OUT.at(i);

		const string L = FLOC + BS +
				A.YEAR + "_" + A.MONTH + "_" + A.NAME + BS +
				A.YEAR + "_" + A.MONTH + "_" + A.NAME + ".htm";

		OUT.at(i).HREF = L;
	}
	return OUT;
}

vector <ICON> generate_FACE (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		OUT.at(i).COLOR = "255, 255, 255";
		OUT.at(i).FACE = "Verdana";
		OUT.at(i).SIZE = "10";
		OUT.at(i).TARGET = "_self";
	}
	return OUT;
}

vector <ICON> generate_PAGE_NAME (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		ostringstream os;

		const string act_NAME = I.at(i).NAME;

		bool prev_SPACE = false;

		for (size_t j = 0; j < act_NAME.size(); j++) {

			char c = act_NAME.at(j);

			const bool SPACE = c == '_';

			const bool UPPER = (j == 0 || prev_SPACE);

			if (!SPACE) {

				if (UPPER)	{

					c = toupper (c);
					os << c << flush;
				}
				else os <<  c << flush;

				prev_SPACE = false;
			}
			else os << ' ' << flush;

			if (SPACE) prev_SPACE = true;
		}
		OUT.at(i).PAGE_NAME = os.str();
	}
	return OUT;
}

vector <ICON> tidy_PAGE_NAME (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	ifstream T;
	T.open (TLST.c_str());

	vector <vector <string> > TIDY;

	while (!T.eof()) {

		vector <string> buf;

		string tidy_this;
		string to_this;

		getline (T, tidy_this, '\t');
		getline (T, to_this, '\n');

		buf.push_back (tidy_this);
		buf.push_back (to_this);

		TIDY.push_back (buf);
	}

	for (size_t i = 0; i < OUT.size(); i++) {
		for (size_t j = 0; j < TIDY.size(); j++) {

			if (OUT.at(i).PAGE_NAME == TIDY.at(j).at(0)) {

				cout << "    Label '" << OUT.at(i).PAGE_NAME << "' has been changed to '" << flush;

				OUT.at(i).PAGE_NAME = TIDY.at(j).at(1);

				cout << OUT.at(i).PAGE_NAME << "'." << endl;
			}
		}
	}
	return OUT;
}

vector <ICON> generate_ICONNAME (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		const ICON A = OUT.at(i);

		const string IN = ILOC + BS + A.YEAR + "_" + A.MONTH + "_" + A.NAME + ITAG;

		OUT.at(i).ICON_FILENAME = IN;
	}
	return OUT;
}

vector <ICON> generate_TITLE (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		//OUT.at(i).TITLE = OUT.at(i).MONTH + "/" + OUT.at(i).YEAR + " - " + OUT.at(i).PAGE_NAME;
		OUT.at(i).TITLE = OUT.at(i).LINKTEXT;

	}
	return OUT;
}

string return_roman_MONTH (const string M) {

	if 		(M == "01") return "I";
	else if (M == "02") return "II";
	else if (M == "03") return "III";
	else if (M == "04") return "IV";
	else if (M == "05") return "V";
	else if (M == "06") return "VI";
	else if (M == "07") return "VII";
	else if (M == "08") return "VIII";
	else if (M == "09") return "IX";
	else if (M == "10") return "X";
	else if (M == "11") return "XI";
	else return "XII";
}

vector <ICON> generate_LINKTEXT (const vector <ICON>& I) {

	vector <ICON> OUT = I;

	for (size_t i = 0; i < OUT.size(); i++) {

		const string Y = OUT.at(i).YEAR;

		const string M = return_roman_MONTH (OUT.at(i).MONTH);

		OUT.at(i).LINKTEXT = Y + ". " + M + " - " + OUT.at(i).PAGE_NAME;
	}

	return OUT;
}

bool by_ID (const ICON& x, const ICON& y) {

	return x.ID < y.ID;
}

bool by_rev_ID (const ICON& x, const ICON& y) {

	return x.ID > y.ID;
}

vector < vector < vector <ICON> > > generate_ICONMATRIX (const vector <ICON>& I) {

	vector < vector < vector <ICON> > > OUT;
	vector < vector <ICON> > buf2;
	vector < ICON> buf;

	vector <ICON> P = I;

	sort (P.begin(), P.end(), by_rev_ID);

	ICON dummy;

	dummy.YEAR = "xxxx";
	dummy.MONTH = "zz";
	dummy.NAME = "rrr";

	P.push_back(dummy);

	for (size_t i = 0; i < P.size() - 1; i++) {

		const ICON A = P.at(i);
		const ICON N = P.at(i+1);
		const bool YR_EQ = A.YEAR == N.YEAR;
		const bool MT_EQ = A.MONTH == N.MONTH;
		const bool LAST = i == P.size() - 2;

		buf.push_back (A);

		if (LAST || !MT_EQ) {

			sort (buf.begin(), buf.end(), by_ID);

			buf2.push_back(buf);
			buf.clear();
		}

		if (LAST || !YR_EQ) {

			OUT.push_back(buf2);
			buf2.clear();
		}
	}
	return OUT;
}

void dbg_cout_I (const vector <ICON> & I) {

	for (size_t i = 0; i < I.size(); i++) {

		cout << "-------------------- RECORD --------------------" << endl;

		cout << "ID...........: " << I.at(i).ID << endl;
		cout << "TITLE........: " << I.at(i).TITLE << endl;
		cout << "NAME.........: " << I.at(i).NAME << endl;
		cout << "ORIGINAL NAME: " << I.at(i).ORIGINAL_NAME << endl;
		cout << "PAGE NAME....: " << I.at(i).PAGE_NAME << endl;
		cout << "FILE NUMBER..: " << I.at(i).FILE_NUMBER << endl;
		cout << "SIZE.........: " << I.at(i).SIZE << endl;
		cout << "YEAR.........: " << I.at(i).YEAR << endl;
		cout << "MONTH........: " << I.at(i).MONTH << endl;
		cout << "ICON NAME....: " << I.at(i).ICON_FILENAME << endl;
		cout << "LINK TEXT....: " << I.at(i).LINKTEXT << endl;
		cout << "HREF.........: " << I.at(i).HREF << endl;
		cout << "TARGET.......: " << I.at(i).TARGET << endl;
		cout << "COLOR........: " << I.at(i).COLOR << endl;
		cout << "FACE.........: " << I.at(i).FACE << endl;
	}
}

void dbg_cout_I_vvv (const vector < vector < vector <ICON> > >& I_vvv) {

	for (size_t i = 0; i < I_vvv.size(); i++) {

		cout << " -------- NEW YEAR -------- " << endl;

		for (size_t j = 0; j < I_vvv.at(i).size(); j++) {

			cout << " -------- NEW MONTH -------- " << endl;

			for (size_t k = 0; k < I_vvv.at(i).at(j).size(); k++) {

				cout << I_vvv.at(i).at(j).size() << endl;
			}
		}
	}
}

int main () {

	vector <string> N = return_FOLDERS_with_order ();

	if (! check_folders (N)) return 101;

	if (! check_icons (N)) return 102;

	vector <ICON> I = generate_ORIGINAL_NAMES (N);

	I = return_FILE_NUMBER (I);

	I = generate_YEAR_MONTH (I);

	I = generate_NAME (I);

	I = generate_HREF (I);

	I = generate_FACE (I);

	I = generate_PAGE_NAME (I);

	I = tidy_PAGE_NAME (I);

	I = generate_LINKTEXT (I);

	I = generate_TITLE (I);

	I = generate_ICONNAME (I);

	//dbg_cout_I (I);

	sort (I.begin(), I.end(), by_rev_ID);

	cout_html (I);

	cout << endl << endl << "DONE" << endl;

	return 0;
}
