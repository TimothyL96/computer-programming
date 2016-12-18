//*********************************************************
//*********************************************************
//**                Song Management System               **
//*********************************************************
//**            TCP 1121    -   Computer Programming     **
//*********************************************************
//**                                                     **
//**            Lim Wei Lun     1142701007               **
//**            Timothy Lam     1142700462               **
//**            Teoh Jie Sheng  11427022368              **
//**                                                     **
//*********************************************************
//*********************************************************


//**********************DO NOT DELETE**********************
//*********************************************************
//**                        TODO                         **
//*********************************************************
//**           1)  Song artist & name uppercase          **
//**           2)  Color system                          **
//**           3)  Loading Bar (a new function)          **
//*********************************************************

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <algorithm>

using namespace std;

class song
{
    private:
        static vector<int> index;
        static vector<string> songname;
        static vector<string> songartist;
        static vector<string> songgenre;
        static int readflag, writeflag;

        //***************************************
        //Get values of static vector variables
        //***************************************
        vector<string> gindex()
        {
            vector<string> tmp;
            stringstream ss;
            for (unsigned int i = 0; i < index.size(); i++)
            {
                ss << index.at(i);
                tmp.push_back(ss.str());
                ss.str("");
            }
            return tmp;
        }

        vector<string> gname()
        {
            return songname;
        }

        vector<string> gartist()
        {
            return songartist;
        }

        vector<string> ggenre()
        {
            return songgenre;
        }

    public:
        //**********************
        //Write vector to file
        //**********************
        void wfile()
        {
            ofstream file("SongList.txt");
            if (!file.is_open())
            {
                cout << "\nError: Unable to Open File. Press any key to quit";
                while (kbhit())
                    getch();
                getch();
                exit(EXIT_FAILURE);
            }
            // SONG ARTIST ALPHABET FOR FIRST CHARACTER
            for (unsigned int i = 0; i < index.size(); i++)
            {
                file << index.at(i) << '\t' << songname.at(i) << '\t' << songartist.at(i) << '\t' << songgenre.at(i) << endl;
                file.flush();
            }
            file.close();

            //COMMENTED OUT AS WRITING TO FILE BECAME AN OPTION
            //PREVIOUSLY EVERY FUNCTION WILL AUTOMATICALLY WRITE TO FILE
            //index.clear();
            //songname.clear();
            //songartist.clear();
            //songgenre.clear();

            //TURN ON WRITEFLAG
            writeflag = 1;
        }

        //**********************
        //Read vector to file
        //**********************
        void rfile()
        {
            vector<string> read;
            ifstream file("SongList.txt");
            if (!file.is_open())
            {
                return;
            }
            while(!file.eof())
            {
                string str, getstr;
                getline(file, str);
                stringstream ss(str);
                while (getline(ss, getstr, '\t'))
                {
                    read.push_back(getstr);
                }
            }
            for (unsigned int i = 0, j = 4; i < read.size(); i++)
            {
                if (i%j == 0)
                    index.push_back(atoi(read.at(i).c_str()));
                if (i%j == 1)
                    songname.push_back(read.at(i));
                if (i%j == 2)
                    songartist.push_back(read.at(i));
                if (i%j == 3)
                    songgenre.push_back(read.at(i));
            }
            //TURN ON READFLAG
            readflag = 1;
        }

        //******************************************
        //Identify which get value function to run
        //******************************************
        vector<string> getval(string sg)
        {
            try
            {
                if (sg == "gindex")
                    return gindex();
                else if (sg == "gname")
                    return gname();
                else if (sg == "gartist")
                    return gartist();
                else if (sg == "ggenre")
                    return ggenre();
                else
                    throw false;
                cout << "Return success!\n";
            }catch(bool)
            {
                cout << "Software error. Please contact Developer.\n";
                cout << "Press any key to quit ";
                while (kbhit())
                    getch();
                exit(EXIT_FAILURE);
            }
        }

        //************************************************************************
        //Convert vector string to vector int
        //Because get value function of vector index returns type vector<string>
        //************************************************************************
        vector<int> vstrtovint(vector<string> snum)
        {
            vector<int> vnum;
            for (unsigned int i = 0; i < snum.size(); i++)
            {
                vnum.push_back(atoi(snum.at(i).c_str()));
            }
            return vnum;
        }

        //**********************************
        //Set value for different functions
        //**********************************
        void setval(string ss[4])
        {
            //ADD
            index.push_back(atoi(ss[0].c_str()));
            songname.push_back(ss[1]);
            songartist.push_back(ss[2]);
            songgenre.push_back(ss[3]);
            writeflag = 0;
        }

        void setval(string ss[4], int index)
        {
            //EDIT
            this->index.at(index) = atoi(ss[0].c_str());
            songname.at(index) = ss[1];
            songartist.at(index) = ss[2];
            songgenre.at(index) = ss[3];
            writeflag = 0;
        }

        void setval(int index)
        {
            //REMOVE
            this->index.erase(this->index.begin() + index);
            songname.erase(songname.begin() + index);
            songartist.erase(songartist.begin() + index);
            songgenre.erase(songgenre.begin() + index);
            writeflag = 0;
        }

        void setindex(vector<int> index)
        {
            //EDIT INDEX ONLY
            this->index = index;
        }

        //**************************************************
        //Get readflag value to check whether file was read
        //**************************************************
        int getreadflag()
        {
            return readflag;
        }

        //**************************************************
        //Get write value to check whether file was written
        //**************************************************
        int getwriteflag()
        {
            return writeflag;
        }
};

//******************************************
//Initialize static members for class "song"
//******************************************
vector<int> song::index;
vector<string> song::songname;
vector<string> song::songartist;
vector<string> song::songgenre;
int song::readflag = 0, song::writeflag = 1;

class searchsort
{
    private:
        song songo;
    public:
        //*****************************************************
        //Binary search vector index for value entered by user
        //*****************************************************
        int searchindex(vector<int> vnum, int value)
        {
            //BINARY SEARCH
            songo.setindex(sortindex(songo.vstrtovint(songo.getval("gindex"))));
            int foundindex = -1, ibegin = 0, iend = vnum.size() - 1;
            unsigned int middle = (ibegin + iend)/2;
            if (middle == 0)
            {
                for (unsigned int i = 0; i < vnum.size(); i++)
                {
                    if (vnum.at(i) == value)
                    {
                        foundindex = i;
                        return foundindex;
                    }
                }
            }
            while (foundindex == -1 && middle >= 0 && middle < vnum.size())
            {
                if (ibegin >= iend && value != vnum.at(middle))
                {
                    break;
                }
                if (value < vnum.at(middle))
                {
                    iend = middle - 1;
                    middle = (ibegin + iend)/2;
                }
                if (value > vnum.at(middle))
                {
                    ibegin = middle + 1;
                    middle = (ibegin + iend)/2;
                }
                if (value == vnum.at(middle))
                {
                    foundindex = middle;
                    break;
                }
            }
            return foundindex;
        }

        //***************************************************************************
        //Time Constrained: Use STD algorithm to sort vector index for binary search
        //**Binary search needs the array/vector to be sorted!
        //***************************************************************************
        vector<int> sortindex(vector<int> vnum)
        {
            sort(vnum.begin(), vnum.end());
            return vnum;
        }
};

class indexcheck
{
    private:
        int foundindexcheck;
        searchsort sso;
        song songo;
    public:
        //**********************************************
        //Check index for duplication to prevent errors
        //**********************************************
        int icheck(int num, int foundindex)
        {
            foundindexcheck = sso.searchindex(songo.vstrtovint(songo.getval("gindex")), num);
            if (foundindex == -1)
            {
                while (foundindexcheck != -1)
                {
                    cout << "Error! Song index exist. ";
                    cout << "Re-enter song index: ";
                    while (!(cin >> num || (num < 0 && num != -1)))
                    {
                        cout << "Error: Enter only integers! : ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                    }
                    cin.clear();
                    cin.ignore(999999, '\n');
                    foundindexcheck = sso.searchindex(songo.vstrtovint(songo.getval("gindex")), num);
                }
            }else
            {
               while (foundindexcheck != -1 && num != songo.vstrtovint(songo.getval("gindex")).at(foundindex))
                {
                    cout << "Error! Song index exist. ";
                    cout << "Reenter song index: ";
                    while (!(cin >> num || (num < 0 && num != -1)))
                    {
                        cout << "Error: Enter only integers! : ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                    }
                    cin.clear();
                    cin.ignore(999999, '\n');
                    foundindexcheck = sso.searchindex(songo.vstrtovint(songo.getval("gindex")), num);
                }
            }
            return num;
        }
};

class sfunction
{
    //***************************************************************************
    //THIS IS A BASE CLASS TO BE INHERITED BY OTHER CLASS FOR FUNCTIONS
    //THIS CLASS IS AN ABSTRACT CLASS AND NO OBJECT OF THIS CLASS CAN BE CREATED
    //THIS IS EQUIVALANT OF INTERFACE IN JAVA
    //***************************************************************************
    // void run() AND bool runrep() MUST BE IMPLEMENTED
    // void run() IS FOR IMPLEMENTING THE MAIN FUNCTINOS
    // bool runrep() IS TO ASK USER WHETHER TO REPEAT FUNCTION
    // PROMPT
    //***************************************************************************
    protected:
        int num, foundindex, type;
        string snum, sname, sartist, sgenre, vals[4];
        char comfirm, cond;
        song songo;
        searchsort sso;
        indexcheck ico;
        virtual void run() = 0;
        virtual bool runrep() = 0;

        sfunction()
        {
            //INITIALIZE MEMBER
            comfirm = 0;
            foundindex = -1;
        }
};

class addc: public sfunction
{
    //*************************
    //FUNCTION FOR ADDING SONG
    //*************************
    private:
        bool runrep()
        {
            char cond;
            cout << "\nSong Added\n"; //tell the user the song is added
            cout << "Do you want to continue add a new song?[y/n]: "; //ask user want to continue to add a new song or not
            cin >> cond; //user input this to determind continue to add a new song or not
            while (cond != 'y' && cond !='Y' && cond != 'N' && cond != 'n')
            {
                cout << "Only enter [y/n]: ";
                cin.clear();
                cin.ignore(9999999, '\n');
                cin >> cond;
            }
            if (cond == 'Y' || cond =='y')
                return true;
            if (cond == 'N' || cond == 'n')
                return false;
            return false;
        }

    public:
        void run()
        {
            cout << "Add song mode" << endl;
            do
            {
                system("cls");
                cout << "Enter song index [positive integers] (-1 to return) : ";
                while (!(cin >> num) || num < -1)
                {
                    cout << "Error: Enter only positive integers! : ";
                    cin.clear();
                    cin.ignore(999999, '\n');
                }
                cin.clear();
                cin.ignore(999999, '\n');
                num = ico.icheck(num, foundindex);
                if (num == -1)
                    break;
                cout << "Enter song name: ";
                getline(cin, sname);
                cout << "Please enter the song's artist: ";
                getline(cin, sartist);
                //Only alphabet
                cout << "Please enter the song genre: ";
                getline(cin, sgenre);
                //List different genres

                itoa(num, &snum[0u], 10);
                vals[0] = &snum[0u];
                vals[1] = sname;
                vals[2] = sartist;
                vals[3] = sgenre;
                songo.setval(vals);
            }while (runrep());
        }
};

class editc: public sfunction
{
    //**************************
    //FUNCTION FOR EDITING SONG
    //**************************
    private:
        bool runrep()
        {
            char cond;
            cout << "Do you want to continue editing songs? [y/n] : ";
            cin >> cond; //user input this to determind continue to add a new song or not
            while (cond != 'y' && cond !='Y' && cond != 'N' && cond != 'n')
            {
                cout << "Only enter [y/n]: ";
                cin.clear();
                cin.ignore(9999999, '\n');
                cin >> cond;
            }
            if (cond == 'Y' || cond =='y')
                return true;
            if (cond == 'N' || cond == 'n')
                return false;
            return false;
        }

    public:
        void run()
        {
            cout << "Edit song mode" << endl;
            do
            {
                system("cls");
                cout <<"Enter the index of the song to edit (-1 to return): ";
                while (!(cin >> num) || (num < 0 && num != -1))
                {
                    cout << "Error: Enter only positive integers! : ";
                    cin.clear();
                    cin.ignore(999999, '\n');
                }
                cin.clear();
                cin.ignore(999999, '\n');
                //take integers, input 2w works and error cin
                if (num == -1)
                    break;
                foundindex = sso.searchindex(songo.vstrtovint(songo.getval("gindex")), num);
                system("cls");
                if (foundindex != -1)
                {
                    sname = songo.getval("gname").at(foundindex);
                    sartist = songo.getval("gartist").at(foundindex);
                    sgenre = songo.getval("ggenre").at(foundindex);
                    cout << "Song Index:\t" << num << endl;
                    cout << "Song Name:\t" << sname << endl;
                    cout << "Song Artist:\t" << sartist << endl;
                    cout << "Song Genre:\t" << sgenre << endl;
                    cout << "\nEnter new infomation:\n";
                    cout << "\nEnter song index: ";
                    while (!(cin >> num))
                    {
                        cout << "Error: Enter only integers! : ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                    }
                    cin.clear();
                    cin.ignore(999999, '\n');
                    num = ico.icheck(num, foundindex);

                    cout << "Enter song name: ";
                    cin.clear();
                    getline(cin, sname);
                    cout << "Enter song artist: ";
                    getline(cin, sartist);
                    cout << "Enter song genre: ";
                    getline(cin, sgenre);

                    //Loading bar

                    itoa(num, &snum[0u], 10);
                    vals[0] = &snum[0u];
                    vals[1] = sname;
                    vals[2] = sartist;
                    vals[3] = sgenre;
                    songo.setval(vals, foundindex);
                    cout << "\nEdit success! ";
                }else
                {
                    cout << "Error: Song index \"" << num << "\" not found! Try again.\n";
                }
            }while (runrep());
        }
};

class remc: public sfunction
{
    //***************************
    //FUNCTION FOR REMOVING SONG
    //***************************
    private:
        bool runrep()
        {
            char cond;
            cout << "Do you want to continue deleting songs? [y/n] : ";
            cin >> cond; //user input this to determind continue to add a new song or not
            while (cond != 'y' && cond !='Y' && cond != 'N' && cond != 'n')
            {
                cout << "Only enter [y/n]: ";
                cin.clear();
                cin.ignore(9999999, '\n');
                cin >> cond;
            }
            if (cond == 'Y' || cond =='y')
                return true;
            if (cond == 'N' || cond == 'n')
                return false;
            return false;
        }

    public:
        void run()
        {
            cout <<"Delete song mode" << endl;
            do
            {
                system("cls");
                do
                {
                    cout <<"Enter the index of the song to delete (-1 to return): ";
                    while (!(cin >> num))
                    {
                        cout << "Error: Enter only integers! : ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                    }
                    cin.clear();
                    cin.ignore(999999, '\n');
                    //take integers, input 2w works and error cin
                    if (num == -1)
                        break;
                    foundindex = sso.searchindex(songo.vstrtovint(songo.getval("gindex")), num);
                    system("cls");
                    comfirm = '0';
                    if (foundindex != -1)
                    {
                        sname = songo.getval("gname").at(foundindex);
                        sartist = songo.getval("gartist").at(foundindex);
                        sgenre = songo.getval("ggenre").at(foundindex);
                        cout << "Song Index:\t" << num << endl;
                        cout << "Song Name:\t" << sname << endl;
                        cout << "Song Artist:\t" << sartist << endl;
                        cout << "Song Genre:\t" << sgenre << endl;
                        cout << "\nAre you sure you want to remove this record? [y/n]: ";
                        while (!(cin >> comfirm) || (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n'))
                        {
                            cout << "Error: Enter only [y/n]! : ";
                            cin.clear();
                            cin.ignore(999999, '\n');
                        }
                        cin.clear();
                        cin.ignore(999999, '\n');
                        if (comfirm == 'Y' || comfirm == 'y')
                        {
                            //Delete success!
                            songo.setval(foundindex);
                            cout << "Delete success!\n";
                        }else
                        {
                            cout << "Song delete canceled. ";
                        }
                    }else
                    {
                        cout << "Error: Song index \"" << num << "\" not found! Try again.\n";
                        comfirm = '1';
                    }
                }while (comfirm == '1');
                if (num == -1)
                        break;
            }while (runrep());
        }
};

class searchc: public sfunction
{
    //*****************************
    //FUNCTION FOR SEARCHING SONGS
    //*****************************
    private:
        bool runrep()
        {
            char cond;
            cout << "Do you want to continue searching songs? [y/n] : ";
            cin >> cond; //user input this to determind continue to add a new song or not
            while (cond != 'y' && cond !='Y' && cond != 'N' && cond != 'n')
            {
                cout << "Only enter [y/n]: ";
                cin.clear();
                cin.ignore(9999999, '\n');
                cin >> cond;
            }
            if (cond == 'Y' || cond =='y')
                return true;
            if (cond == 'N' || cond == 'n')
                return false;
            return false;
        }

    public:
        //TO LOWER
        void run()
        {
            vector<int> found;
            cout <<"Search song mode" << endl;
            do
            {
                foundindex = -1;
                system("cls");
                do
                {
                    found.clear();
                    cout <<"Choose which song detail to search (-1 to return)\n";
                    cout << "(1) Song Index\n(2) Song Name\n(3) Song Artist\n(4) Song Genre\n";
                    cout << "Your choice: ";
                    while (!(cin >> type))
                    {
                        cout << "Error: Enter only integers! : ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                    }
                    //take integers, input 2w works and error cin
                    while (type > 4 || type == 0 || type < -1)
                    {
                        cout << "Error: Choose only 1-4 (-1 to return): ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                        while (!(cin >> type))
                        {
                            cout << "Error: Enter only integers! : ";
                            cin.clear();
                            cin.ignore(999999, '\n');
                        }
                    }
                    if (type == -1)
                        break;
                    cin.clear();
                    cin.ignore(999999, '\n');
                    system("cls");
                    switch (type)
                    {
                        case 1:
                            cout << "Enter index of song to search: ";
                            while (!(cin >> num))
                            {
                                cout << "Error: Enter only integers! : ";
                                cin.clear();
                                cin.ignore(999999, '\n');
                            }
                            cin.clear();
                            cin.ignore(999999, '\n');
                            foundindex = sso.searchindex(songo.vstrtovint(songo.getval("gindex")), num);
                            break;
                        case 2:
                            cout << "Enter name of song to search: ";
                            getline(cin, sname);
                            for (unsigned int i = 0; i < songo.getval("gname").size(); i++)
                            {
                                if (songo.getval("gname").at(i).find(sname) != string::npos)
                                {
                                    found.push_back(i);
                                }
                            }
                            break;
                        case 3:
                            cout << "Enter artist of song to search: ";
                            getline(cin, sartist);
                            for (unsigned int i = 0; i < songo.getval("gartist").size(); i++)
                            {
                                if (songo.getval("gartist").at(i).find(sartist) != string::npos)
                                {
                                    found.push_back(i);
                                }
                            }
                            break;
                        case 4:
                            cout << "Enter genre of song to search: ";
                            getline(cin, sgenre);
                            for (unsigned int i = 0; i < songo.getval("ggenre").size(); i++)
                            {
                                if (songo.getval("ggenre").at(i).find(sgenre) != string::npos)
                                {
                                    found.push_back(i);
                                }
                            }
                            break;
                        default:
                            cout << "\nOption error. Please contact Developer.\nPress any key to quit";
                            while (kbhit())
                                getch();
                            getch();
                            exit(EXIT_FAILURE);
                    }

                    comfirm = '0';
                   // system("cls");
                    if (foundindex != -1)
                    {
                        sname = songo.getval("gname").at(foundindex);
                        sartist = songo.getval("gartist").at(foundindex);
                        sgenre = songo.getval("ggenre").at(foundindex);
                        cout << "Song found!\n";
                        cout << "Song Index:\t" << num << endl;
                        cout << "Song Name:\t" << sname << endl;
                        cout << "Song Artist:\t" << sartist << endl;
                        cout << "Song Genre:\t" << sgenre << endl;

                    }else if (found.size() != 0)
                    {
                        if (found.size() > 1)
                            cout << "Songs found!\n";
                        else
                            cout << "Song found!\n";

                        for (unsigned int i = 0; i < found.size(); i++)
                        {
                            snum = songo.getval("gindex").at(found.at(i));
                            sname = songo.getval("gname").at(found.at(i));
                            sartist = songo.getval("gartist").at(found.at(i));
                            sgenre = songo.getval("ggenre").at(found.at(i));
                            cout << "Song Index:\t" << snum << endl;
                            cout << "Song Name:\t" << sname << endl;
                            cout << "Song Artist:\t" << sartist << endl;
                            cout << "Song Genre:\t" << sgenre << endl << endl;
                        }
                    }else
                    {
                        switch (type)
                        {
                            cout << endl;
                            case 1:
                                cout << "Error: Song index \"" << num << "\" not found! Try again?\n";
                                break;
                            case 2:
                                cout << "Error: Song name \"" << sname << "\" not found! Try again?\n";
                                break;
                            case 3:
                                cout << "Error: Song artist \"" << sartist << "\" not found! Try again?\n";
                                break;
                            case 4:
                                cout << "Error: Song genre \"" << sgenre << "\" not found! Try again?\n";
                                break;
                        }
                        comfirm = '1';
                    }
                }while (comfirm == '1');
                if (type == -1)
                        break;
            }while (runrep());
        }
};

class viewallc: public sfunction
{
    //*******************************
    //FUNCTION FOR VIEWING ALL SONGS
    //*******************************
    private:
        bool runrep()
        {
            cout << "Hello World! I do literally nothing! :D \n";
            return true;
        }

    public:
        void run()
        {
            if (songo.getval("gindex").empty())
                cout << "No songs saved\n";
            for (unsigned int i = 0; i < songo.getval("gindex").size(); i++)
            {
                cout << "Song Index:\t" << songo.getval("gindex").at(i) << endl;
                cout << "Song Name:\t" << songo.getval("gname").at(i) << endl;
                cout << "Song Artist:\t" << songo.getval("gartist").at(i) << endl;
                cout << "Song Genre:\t" << songo.getval("ggenre").at(i) << endl << endl;
            }
            while (kbhit())
                getch();
            cout << "Press any key to go back.";
            getch();

            //TABLE VIEW
            /*unsigned int maxindex = songo.getval("gindex").at(0).length(), maxname = songo.getval("gname").at(0).length(), maxartist = songo.getval("gartist").at(0).length(), maxgenre = songo.getval("ggenre").at(0).length();
            for (unsigned int i = 1; i < songo.getval("gindex").size(); i++)
            {
                if (songo.getval("gindex").at(i - 1).length() <= songo.getval("gindex").at(i).length() && maxindex < songo.getval("gindex").at(i).length())
                    maxindex = songo.getval("gindex").at(i).length();
                if (songo.getval("gname").at(i - 1).length() <= songo.getval("gname").at(i).length() && maxname < songo.getval("gname").at(i).length())
                    maxname = songo.getval("gname").at(i).length();
                if (songo.getval("gartist").at(i - 1).length() <= songo.getval("gartist").at(i).length() && maxartist < songo.getval("gartist").at(i).length())
                    maxartist = songo.getval("gartist").at(i - 1).length();
                if (songo.getval("ggenre").at(i).length() <= songo.getval("ggenre").at(i).length() && maxgenre < songo.getval("ggenre").at(i).length())
                    maxgenre = songo.getval("ggenre").at(i).length();
            }
            cout << "|  Song Index  |" << "\tSong Name\t" << "|\tSong Artist \t|" << "  Song Genre  |";
            for (unsigned int i = 0; i < songo.getval("gindex").size() - 1; i++)
            {
                for (int i = 0; i < 80; i++)
                {
                    //cout << i;
                    cout << "-";
                }
                cout << "|" << setw(7 - songo.getval("gindex").at(i).length()/2) << setfill('x') << songo.getval("gindex").at(i) << setw(12 - songo.getval("gindex").at(i).length()) << " " ;
                cout << "|" << setw(11 - songo.getval("gindex").at(i).length() + songo.getval("gindex").at(i).length()/2) << " " << songo.getval("gname").at(i) << setw(11 - songo.getval("gindex").at(i).length() + songo.getval("gindex").at(i).length()) << " ";
                cout << "|" << songo.getval("gartist").at(i) << setw(21 - songo.getval("gartist").at(i).length()) << " ";
                cout << "|" << songo.getval("ggenre").at(i) << setw(13 - songo.getval("ggenre").at(i).length()) << " |";
            }*/
        }
};

class wfilec: public sfunction
{
    //*************************************
    //FUNCTION FOR WRITING SONGS INTO FILE
    //*************************************
    private:
        bool runrep()
        {
            cout << "Hello World! I do literally nothing! :D \n";
            return true;
        }

    public:
        void run()
        {
            //CHECK FOR FILE EXISTANCE
            ifstream file("SongList.txt");
            if(file.is_open())
            {
                cout << "Note: Your data in the file will be replaced. Remember to read them first!\n\n";
                cout << "You have not save the current data into a file.\nContinue loading from file will cause all current data to be deleted.\nDo you want to proceed? [y/n]: ";
                cin >> comfirm;
                while (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n')
                {
                    cout << "Error. Only enter [y/n]: ";
                    cin.clear();
                    cin.ignore(9999999, '\n');
                    cin >> comfirm;
                    //FIrst value valid then rest not counted
                }
                if (comfirm == 'N' || comfirm == 'n')
                {
                    return;
                }
            }
            //LOADING BAR
            //Run Write File
            songo.setindex(sso.sortindex(songo.vstrtovint(songo.getval("gindex"))));
            songo.wfile();
            system("cls");
            cout << "Write success!\nPress any key to return\n";
            while (kbhit())
                getch();
            getch();
        }
};

class rfilec: public sfunction
{
    //*************************************
    //FUNCTION FOR READING SONGS INTO FILE
    //*************************************
    private:
        bool runrep()
        {
            cout << "Hello World! I do literally nothing! :D \n";
            return true;
        }

    public:
        void run()
        {
            //IF READFLAG IS SET
            //ASK COMFIRMATION AS READING FROM FILE WILL APPEND *NOT* RESETTING THOSE VECTORS
            if (songo.getreadflag() == 1)
            {
                cout << "You have previously read from the file.\nDoing so again will append all data from the file to your current session which might cause index duplication.\nDo you wish to continue? [y/n]: ";
                cin >> comfirm;
                while (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n')
                {
                    cout << "Error. Only enter [y/n]: ";
                    cin.clear();
                    cin.ignore(9999999, '\n');
                    cin >> comfirm;
                    //FIrst value valid then rest not counted
                }
                if (comfirm == 'N' || comfirm == 'n')
                {
                    return;
                }
            }
            //LOADING BAR
            songo.rfile();
            system("cls");
            if (songo.getreadflag() == 0)
            {
                cout << "Error! File not found.\nPress any key to return.";
                while (kbhit())
                    getch();
                getch();
            }else
            {
                cout << "Read success!\nPress any key to return.";
                while (kbhit())
                    getch();
                getch();
            }
        }
};

class optionc: public sfunction
{

    //***************************************************
    //DIFFERENT OPTIONS FOR USERS
    //INCLUDING AUTO READING PREVIOUS SESSION AT STARTUP
    //***************************************************
    private:

        bool runrep()
        {
            cout << "Do you want to run this function again?\n";
                cout << "Enter [y/n]: ";
                cin >> comfirm;
                while (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n')
                {
                    cout << "Error. Only enter [y/n]: ";
                    cin.clear();
                    cin.ignore(9999999, '\n');
                    cin >> comfirm;
                    //FIrst value valid then rest not counted
                }
                if (comfirm == 'N' || comfirm == 'n')
                {
                    return false;
                }
            return true;
        }

        //CHECK IF CONFIG HEADING IS CORRECT
        //BAD GUY USER MIGHT TRY TO CHANGE THE FILE config.ini
        vector<string> checkconf()
        {
            vector<string> read = readconf();
            for (unsigned int i = 0; i < read.size()/2; i += 2)
            {
                if (read.at(i) != "autoread" /*and other config title using &&*/)
                {
                    read.erase(read.begin() + i);
                }
            }
            return read;
        }
        //FUNCTION TO ASK USER FOR ENABLING/DISABLING AUTO READING PREVIOUS SESSION FILE DATA
        void autoread()
        {
            system("cls");
            vector<string> read = readconf();
            if (!read.empty())
            {
                for (unsigned int i = 0; i < read.size()/2; i += 2)
                {
                    if (read.at(i) == "autoread")
                    {
                        if (read.at(i+1) == "false")
                        {
                            cout << "Do you want to enable auto-read?\nThis function will automatically restore your previous sesssion at startup.\n";
                            cout << "Enter [y/n]: ";
                            cin >> comfirm;
                            while (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n')
                            {
                                cout << "Error. Only enter [y/n]: ";
                                cin.clear();
                                cin.ignore(9999999, '\n');
                                cin >> comfirm;
                                //FIrst value valid then rest not counted
                            }
                            if (comfirm == 'N' || comfirm == 'n')
                            {
                                return;
                            }
                            read.at(i+1) = "true";
                            writeconf(read);
                            break;
                        }else
                        {
                            cout << "Auto-read is enabled. Do you want to disable this function?\nYou can still manually read file using function No.7 at main menu.\n";
                            cout << "Enter [y/n]: ";
                            cin >> comfirm;
                            while (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n')
                            {
                                cout << "Error. Only enter [y/n]: ";
                                cin.clear();
                                cin.ignore(9999999, '\n');
                                cin >> comfirm;
                                //FIrst value valid then rest not counted
                            }
                            if (comfirm == 'N' || comfirm == 'n')
                            {
                                return;
                            }
                            read.at(i+1) = "false";
                            writeconf(read);
                            break;
                        }
                    }
                }
            }else
            {
                cout << "Do you want to enable auto-read?\nThis function will automatically restore your previous sesssion at startup.\n";
                cout << "Enter [y/n]: ";
                cin >> comfirm;
                while (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n')
                {
                    cout << "Error. Only enter [y/n]: ";
                    cin.clear();
                    cin.ignore(9999999, '\n');
                    cin >> comfirm;
                    //FIrst value valid then rest not counted
                }
                if (comfirm == 'N' || comfirm == 'n')
                {
                    return;
                }
                read.push_back("autoread");
                read.push_back("true");
                writeconf(read);
            }
            read = checkconf();
        }
        //FUNCTION TO WRITE CONFIG
        //USED BY ANY OPTIONS TO WRITE ALL CONFIG INTO CONFIG FILE
        void writeconf(vector<string> read)
        {
            ofstream file("config.ini");
            if (!file.is_open())
            {
                cout << "\nError: Unable to Open File. Press any key to quit";
                while (kbhit())
                    getch();
                getch();
                exit(EXIT_FAILURE);
            }
            for (unsigned int i = 0; i < read.size(); i += 2)
            {
                file << read.at(i) << "=" << read.at(i+1) << endl;
            }
            file.close();
            cout << "\nSuccess!. Press any key to return";
            while (kbhit())
                getch();
            getch();
        }
        //FUNCTION FOR COLOR CHANGING
        //COLOR CHANGING FOR BOTH TEXT AND BACKGROUND
        //NOT IMPLEMENTED YET. 23/9/2015 2.03 A.M.
        //changelog, IMPLEMENTED 23/9/205 0536 GMT+0900, DON'T KNOW GMT? GOOGLE PLEASE, THANKS
        void ccolor()
        {
            do
            {
                //Due to my compiler reason, i cannot change the colour, but the code itself can run,
                //so i didn't do loop since i cannot see the different.
                system("cls");//clear screen
                char bg, txt;//variable
                string y = "color ";//variable
                int colour;//variable
                int choice;//variable, do I have to explain much?
                system("cls");//clear screen again~;
                cout << "Please enter the colour you want to choose for text" << endl; //Menu
                cout << "(1) Black\n(2) Blue\n(3) Green\n(4) Aqua\n(5) Red\n(6) Purple\n(7) Yellow" << endl;
                cout << "(8) White\n(9) Gray\n(10) Light blue\n(11) Light Green\n(12) Light Aqua\n(13) Light Red" << endl;
                cout << "(14) Light Purple\n(15) Light Yellow\n(16) Plain White" << endl;
                cout << "Please enter your choice for colour of text (-1 to return): ";//Lazy explain, but begging for input
                //input here please
                while (!(cin >> colour) || colour < -1)
                    {
                        cout << "Error: Enter only positive integers! : ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                    }
                cin.clear();
                cin.ignore(999999, '\n');
                if (colour == -1)
                    return;
                //Exception handling
                try{
                    //this role is the thrower
                    if (colour > 16)
                        throw 2;
                    if (colour < 1)
                        throw 2;
                    if (colour == 0)
                        throw 2;
                    //Done the thrower now go to the real choice
                    switch (colour)
                    {	//Switch case for the colours, according to the menu;
                        case 1:
                            txt = '0';
                            break;
                        case 2:
                            txt = '1';
                            break;
                        case 3:
                            txt = '2';
                            break;
                        case 4:
                            txt = '3';
                            break;
                        case 5:
                            txt = '4';
                            break;
                        case 6:
                            txt = '5';
                            break;
                        case 7:
                            txt = '6';
                            break;
                        case 8:
                            txt = '7';
                            break;
                        case 9:
                            txt = '8';
                            break;
                        case 10:
                            txt = '9';
                            break;
                        case 11:
                            txt = 'A';
                            break;
                        case 12:
                            txt = 'B';
                            break;
                        case 13:
                            txt = 'C';
                            break;
                        case 14:
                            txt = 'D';
                            break;
                        case 15:
                            txt = 'E';
                            break;
                        case 16:
                            txt = 'F';
                            break;
                         default:
                            cout << "Software error! Please contact Developer!\n";
                            cout << "Press any key to quit ";
                            }
                        }
                //catching from the thrower
                catch(int){
                    cout << "only integer between 1 to 16 is allowed!";
                }

                system("cls");
                cout << "Please enter the colour you want to choose for background" << endl; //Menu
                cout << "(1) Black\n(2) Blue\n(3) Green\n(4) Aqua\n(5) Red\n(6) Purple\n(7) Yellow" << endl;
                cout << "(8) White\n(9) Gray\n(10) Light blue\n(11) Light Green\n(12) Light Aqua\n(13) Light Red" << endl;
                cout << "(14) Light Purple\n(15) Light Yellow\n(16) Plain White" << endl;
                cout << "Please enter your choice for colour of background (-1 to return): ";//Lazy explain, but begging for input
                while (!(cin >> colour) || colour < -1)
                {
                    cout << "Error: Enter only positive integers! : ";
                    cin.clear();
                    cin.ignore(999999, '\n');
                }
                cin.clear();
                cin.ignore(999999, '\n');
                if (colour == -1)
                    return;
                try
                {
                //this role is the thrower
                if (colour > 16 || colour < -1 || colour == 0)
                    throw 2;
                //Done the thrower now go to the real choice
                switch (colour)
                {//Switch case, again, for the background colour
                    case 1:
                        bg='0';
                        break;
                    case 2:
                        bg='1';
                        break;
                    case 3:
                        bg='2';
                        break;
                    case 4:
                        bg='3';
                        break;
                    case 5:
                        bg='4';
                        break;
                    case 6:
                        bg='5';
                        break;
                    case 7:
                        bg='6';
                        break;
                    case 8:
                        bg='7';
                        break;
                    case 9:
                        bg='8';
                        break;
                    case 10:
                        bg='9';
                        break;
                    case 11:
                        bg='A';
                        break;
                    case 12:
                        bg='B';
                        break;
                    case 13:
                        bg='C';
                        break;
                    case 14:
                        bg='D';
                        break;
                    case 15:
                        bg='E';
                        break;
                    case 16:
                        bg='F';
                        break;
                    //if user tak mau tukar background colour, please ENTER -1;
                    case -1:
                        return;
                     default:
                        cout << "Software error! Please contact Developer!\n";
                        cout << "Press any key to quit ";
                        while (kbhit)
                            getch();
                        getch;
                    }
                }
                //exception handling, catching, do i have to explain much?
                catch(char){
                cout << "Only integer allowed!";
                cin.clear();
                cin.ignore(999999, '\n');
                }
                catch(int){
                    cout << "only integer between 1 to 16 is allowed!";
                }
                //Handling for bg, because if user don't want to change his colour, he pick -1, which bg will return
                // a random result, the if else statement avoid it from happening.
                y += bg;
                y += txt;//append the first option which is foreground into "Color ", For eg. Now colour evolve into "Color 1"
                //display colour code XDDD
                cout << "Color code is: "<< y <<endl;

                //if the colour code is true;
                if(system(y.c_str()))
                {
                    //Change the colour, HORRAY, NOW YOUR TEXT AND BACKGROUND IS DIFFERENT IF YOU CHANGED IT
                    system(y.c_str());
                    cout << "Colour changed successful! Enjoy your new color!\n";
                }
            }while (runrep());
}

        //THE END FOR TEXT COLOUR CHANGING, ALL PEOPLE, PRAY ZEBRA!
    public:
        void run()
        {
            cout << "(1) Auto-read when program start\n";
            cout << "(2) Change text or background colour\n";
            cout << "(3) Return to main menu\n";
            cout << "Your choice: ";
            do
            {
                while (!(cin >> num))
                {
                    cout << "Error: Choose only integers! : ";
                    cin.clear();
                    cin.ignore(999999, '\n');
                }
                cin.clear();
                cin.ignore(999999, '\n');
                if (num > 3 || num < 1)
                    cout << "Error! Enter only 1-3: ";
                else
                {
                    switch (num)
                    {
                        case 1:
                            autoread();
                            break;
                        case 2:
                            ccolor();
                            break;
                        case 3:
                            return;
                            break;
                        default:
                            cout << "Software error! Please contact Developer!\n";
                            cout << "Press any key to quit ";
                            while (kbhit())
                                getch();
                            getch();
                            exit(EXIT_FAILURE);
                    }
                }
            }while (num > 3 || num < 1);
        }

        //FUNCTION TO READ CONFIGURATION FILE
        vector<string> readconf()
        {
            vector<string> read;
            ifstream file("config.ini");
            if (file.is_open())
            {
                while(!file.eof())
                {
                    string str, getstr;
                    getline(file, str);
                    stringstream ss(str);
                    while (getline(ss, getstr, '='))
                    {
                        read.push_back(getstr);
                    }
                }
            }
            return read;
        }
};

class quitc: public sfunction
{
    private:
        bool runrep()
        {
            cout << "Hello World! I do literally nothing! :D \n";
            return true;
        }

    public:
        void run()
        {
            //IF WRITEFLAG IS OFF. ASK COMFIRMATION FROM USER TO QUIT
            if (songo.getwriteflag() == 0)
            {
                cout << "You have not save your last change.\n";
            }
            cout << "Are you sure you want to quit? [y/n]: ";
            cin >> comfirm;
            while (comfirm != 'Y' && comfirm != 'y' && comfirm != 'N' && comfirm != 'n')
            {
                cout << "Error. Only enter [y/n]: ";
                cin.clear();
                cin.ignore(9999999, '\n');
                cin >> comfirm;
                //FIrst value valid then rest not counted
            }
            if (comfirm == 'N' || comfirm == 'n')
            {
                return;
            }
            //Loading bar. Thank you
            exit(EXIT_SUCCESS);
        }
};

class menuc: public sfunction
{
    //******************************************
    //CLASSES OBJECTS TO BE USED IN SWITCH CASE
    //******************************************
    private:
        addc addo;
        editc edito;
        remc remo;
        searchc so;
        viewallc vo;
        wfilec wo;
        rfilec ro;
        optionc oo;
        quitc qo;

        bool runrep()
        {
            cout << "Hello World! I do literally nothing! :D \n";
            return true;
        }

    public:
        // THE MAIN MENU FOR USER TO INTERACT WITH THE SOFTWARE
        void run()
        {
            do
            {
                system("cls");

                cout << "*****************************************************" << endl;
                cout << "********* Welcome to Song Management System *********" << endl;
                cout << "*****************************************************" << endl;
                cout << "*** Which of the function you would like to use? ****" << endl;
                cout << "** Please select from one of the following choices **" << endl;
                cout << "*****************************************************" << endl << endl;
                cout << "(1) Add songs\n";
                cout << "(2) Edit songs\n";
                cout << "(3) Remove songs\n";
                cout << "(4) Search songs\n";
                cout << "(5) View all songs\n";
                cout << "(6) Save current session\n";
                cout << "(7) Restore previous session\n";
                cout << "(8) Options\n";
                cout << "(9) Exit\n";
                cout << "\nPlease enter the function you want to use: "	;
                do
                {
                    while (!(cin >> num))
                    {
                        cout << "Error: Enter only integers! : ";
                        cin.clear();
                        cin.ignore(999999, '\n');
                    }
                    cin.clear();
                    cin.ignore(999999, '\n');

                    if (num < 1 || num > 9)
                        cout << "Error: Choose from 1-9: ";
                    else
                    {
                        switch (num)
                        {
                            case 1:
                                system("cls");
                                addo.run();
                                break;
                            case 2:
                                system("cls");
                                edito.run();
                                break;
                            case 3:
                                system("cls");
                                remo.run();
                                break;
                            case 4:
                                system("cls");
                                so.run();
                                break;
                            case 5:
                                system("cls");
                                vo.run();
                                break;
                            case 6:
                                system("cls");
                                wo.run();
                                break;
                            case 7:
                                system("cls");
                                ro.run();
                                break;
                            case 8:
                                system("cls");
                                oo.run();
                                break;
                            case 9:
                                system("cls");
                                qo.run();
                                break;
                            default:
                                system("cls");
                                cout << "Software error! Please contact Developer!\n";
                                cout << "Press any key to quit ";
                                while (kbhit())
                                    getch();
                                exit(EXIT_FAILURE);
                        }
                    }
                }while (num < 1 || num > 9);
            }while (true);
        }
};

int main()
{
    //SETTING UP
    //CLASSES OBJECTS AND VECTOR FOR READING CONFIG FILE
    song songo;
    optionc oo;
    menuc mo;
    vector<string> read = oo.readconf();

    //******************************************
    //CHECK CONFIG FILE IF AUTO-READ IS ENABLED
    //******************************************
    for (unsigned int i = 0; i < read.size()/2; i += 2)
    {
        if (read.at(i) == "autoread")
            if (read.at(i+1) == "true")
                songo.rfile();
    }
    system("cls");

    //START THE MAIN MENU
    mo.run();
    return 0;
}
