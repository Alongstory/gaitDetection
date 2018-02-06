//============================================================================
// Name        : gaitcyDetection.cpp
// Author      : Yu Liu
// Version     :
// Copyright   :
// Description :Heel strike
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> //which is related to get( , , ) that has 3 candidates
#include <string>
#include <cstdlib> //for transforming the string to double
#include <dlib/svm.h> //include the dlib library, which gcc version higher than 6.1
using namespace std;

double main() {
	//train the datasets first
	//define the vector which will store the data
	vector< vector<double> > scoreRank1;

	//define every line and its field
	string line, field;

	//open the file
	ifstream extract;
	extract.open("C:\\Users\\Yu\\Desktop\\doubleernChallenge\\Datasets\\walkData1_time_Xa_Za_Yg.csv");

	//extract the data to the vector
	if(extract.is_open())
	{
		//get single line
		while (getline(extract, line))
		{
			istringstream stream(line);
			vector<double> values;

			while(getline(stream, field, ','))
			{
				//transform string doubleo double and input those values to the first 2 columns of rowvector
				double fielddouble;
				fielddouble = atoi(field.c_str());
				values.push_back(fielddouble);
			}
			//output the result doubleo scoreRank1 like time(0), X-accel(1), Z-accel(2), Y-gyro(3)
			scoreRank1.push_back(values);
		}
	}
	else
	{
		cout<<"fail to load"<<endl;
	}
	//close the file, now the dataset1 was stored in vector scoreRank1
	extract.close();
/*******************************************************************************************************/
//start to train of dataset 1

	//define the obj we will rank in dlib way
	typedef dlib::matrix<double,3,1> sample_type;

    // examples of relevant (i.e. high ranking) and non-relevant (i.e. low
    //ranking) vectors and store them doubleo a ranking_pair object like so:
    dlib::ranking_pair<sample_type> data;
    sample_type samp;

/*******************************************************************************************************/
//choose data to train by change the value of j and k

    // Make relevant examples, for dataset1, it should be
    double j = 0, k = 0;	//j is the start podouble of relevant, k is the duration of the relevant set
    for (double i = 0; i <= k ; i++){
    samp = scoreRank1[j][1], scoreRank1[j][2], scoreRank1[j][3];
    data.relevant.push_back(samp);
    }

    // Now make non-relevant examples.
    j = 1; k = 1;
    for (double i = 0; i <= k ; i++){
    samp = scoreRank1[j][1], scoreRank1[j][2], scoreRank1[j][3];
    data.nonrelevant.push_back(samp);
    }


//the end of add data of dataset 1
/*******************************************************************************************************/
//the start of train dataset 2

	//define the vector which will store the data
	vector< vector<double> > scoreRank2;

	extract.open("C:\\Users\\Yu\\Desktop\\doubleernChallenge\\Datasets\\walkData2_time_Xa_Za_Yg.csv");

	//extract the data to the vector
	if(extract.is_open())
	{
		//get single line
		while (getline(extract, line))
		{
			istringstream stream(line);
			vector<double> values;

			while(getline(stream, field, ','))
			{
				//transform string doubleo double and input those values to the first 2 columns of rowvector
				double fielddouble;
				fielddouble = atoi(field.c_str());
				values.push_back(fielddouble);
			}
			//output the result doubleo scoreRank1 like time(0), X-accel(1), Z-accel(2), Y-gyro(3)
			scoreRank2.push_back(values);
		}
	}
	else
	{
		cout<<"fail to load"<<endl;
	}

	extract.close();


//close the file, now the dataset2 was stored in vector scoreRank2
/*******************************************************************************************************/
//choose data to train by change the value of j and k

    // Make relevant examples, for dataset1, it should be
    double j = 0, k = 0;	//j is the start podouble of relevant, k is the duration of the relevant set
    for (double i = 0; i <= k ; i++){
    samp = scoreRank2[j][1], scoreRank2[j][2], scoreRank2[j][3];
    data.relevant.push_back(samp);
    }

    // Now make non-relevant examples.
    j = 1; k = 1;
    for (double i = 0; i <= k ; i++){
    samp = scoreRank2[j][1], scoreRank2[j][2], scoreRank2[j][3];
    data.nonrelevant.push_back(samp);
    }


/*******************************************************************************************************/

    //using linear kernel
    typedef dlib::linear_kernel<sample_type> kernel_type;

    // Now make a trainer and tell it to learn a ranking function based on
    // our data.
    dlib::svm_rank_trainer<kernel_type> trainer;
    dlib::decision_function<kernel_type> rank = trainer.train(data);

    // Now if you call rank on a vector it will output a ranking score.  In
    // particular, the ranking score for relevant vectors should be larger
    // than the score for non-relevant vectors.
    cout << "ranking score for a relevant vector(checking for the threshold): " << rank(data.relevant[0]) << endl;


//the end of train dataset
/*******************************************************************************************************/
//the sumulation of ranking from a real-time data using dataset 1
    vector<vector <double> > scoreRank;
    double threshold = 1; //the threshold of the score, should be refenrenced to the datasets


	extract.open("C:\\Users\\Yu\\Desktop\\doubleernChallenge\\Datasets\\walkData1_time_Xa_Za_Yg.csv");//this root could be changed for other file

	//extract the data to the vector
	if(extract.is_open())
	{
		//get single line
		while (getline(extract, line))
		{
			istringstream stream(line);
			vector<double> values;

			while(getline(stream, field, ','))
			{
				//transform string doubleo double and input those values to the first 2 columns of rowvector
				double fielddouble;
				fielddouble = atoi(field.c_str());
				values.push_back(fielddouble);
			}

			//output the result doubleo scoreRank like time(0), X-accel(1), Z-accel(2), Y-gyro(3), score(4), status(5)
			//now get the score of this line
			samp = values[1], values[2], values[3];
			double score = rank(samp);
			values.push_back(score);

			//judge if it was the heel strike, if it is, status = 1
			if (score > threshold)
				values.push_back(1);
			else
				values.push_back(0);
			//store it into the rank
			scoreRank.push_back(values);
		}
	}
	else
	{
		cout<<"fail to load"<<endl;
	}
	//close the file, now the dataset and its rank was stored in vector scoreRank
	extract.close();

}


