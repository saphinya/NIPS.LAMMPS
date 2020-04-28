#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <ctime>
#include <string>
using namespace std;


int main( int argc, char *argv[])
{
	//start timer
	clock_t begin = clock(); 
	// check input arguments
	if (argc != 6){ 			// this value must be 1 more than number of inputs
		cout << " Incomplete input. Please provide the following in order:\n";
		cout << " 1. number of outputs \n" << " 2. nstep \n" << " 3. x dimension\n";
		cout << " 4. y dimension\n" << " 5. z dimension\n" << endl;
		//cout << " 4. ouptut file name\n"; 
		return 0;
	}
	//------------------------------------
	// initialize variables
	//------------------------------------
	string infilename;
	string outfilename;
	string outfilename2;
	stringstream ss;
	stringstream ss2;
	stringstream ss3;
	int ssTemp = 0;
	int snapshots = atoi(argv[1]);
	int simLength = atoi(argv[2]);
	int x = atoi(argv[3]); // for floats, use atof(argv[])
	int y = atoi(argv[4]);
	int z = atoi(argv[5]);
	//outfilename = argv[4];
	fstream infile;
	ofstream outfile;
	ofstream outfile2;
	int spacing = simLength / snapshots;
	int maxII = simLength / spacing;
	// for 1D scan (x and y)
	int interface = 0;
	double start = 0.0;
	double testStart = 0.0;
	double testPoint = 0.0;
	double solSpace = 0.0;
	double solInter = 0.0;
	// for 2D average (x and y planes at depth z)
	double solInterAvg = 0.0;
	double solInterRun = 0.0;
	double diff = 0.0;
	double diff2 = 0.0;
	double sumDiff2 = 0.0;
	double diff3D = 0.0;
	double diff3D_2 = 0.0;
	double sumDiff3D_2 = 0.0;
	double solAvg3D = 0.0;
	double stdDev3D = 0.0;
	// ---------------------------------------
	//  Allocate Arrays
	// ---------------------------------------
	// vtkoutput
	double ***array3D;
	array3D = new double**[x];
	for (int i = 0; i < x; i++) {
		array3D[i] = new double*[y];
		for (int j = 0; j < y; j++) {
			array3D[i][j] = new double[z];
		}
	}
	// average interfacial distance of 
	// x & z scans for each y depth 
	double* b = NULL;
	b = new double[y];
	for (int k = 0; k<y; k++) {
		b[k] = 0;
	}

	// array for  (solvent spacing)/(2*interfaces) 
	// for x & y scan scan
	double* D = NULL;
	D = new double[x+z];
	for (int k = 0; k< (x + z); k++) {
		D[k] = 0;
	}
	// array for  (solvent spacing)/(2*interfaces)
	// for x scan
	//double* c = NULL;
	//c = new double[z];
	//for (int j = 0; j < z; j++) {
	//	c[j] = 0;
	//}

	// arrays for standard deviation 2D and 3D
	double *stdDev = NULL;
	stdDev = new double[y];
	for (int j = 0; j<y; j++) {
		stdDev[j] = 0;
	}
	//double *stdDev3D = NULL;
	//stdDev3D = new double[ maxII + 1];
	//for (int k = 0; k < maxII + 1 ; k++) {
	//	stdDev3D[k] = 0;
	//}

	// --------------------------------------
	// open output file for 3D average
	// --------------------------------------
	ss3 << simLength << "cubicAvg" << ".csv";
	outfilename2 = ss3.str();       // a copy for ss3
    //sprintf(outfilename2,"%d.cubicAvgกฃcsv",simLength);
	outfile2.open(outfilename2.c_str());
	outfile2 << "nstep,poreSpace,+-\n";

	 //-------------------------------------
	 //opening files ...
	 //-------------------------------------
   //   for (int ii = 0; ii < 1; ii++) {
		 //first v.0.vtk file
		for (int ii = 0; ii < (maxII+1); ii++)
{
			if (ii == 0) {
				ssTemp = ii;
				ss << "v." << ssTemp << ".vtk";
				infilename = ss.str();
			}
		// second v.1.vtk file
			//else if (ii == 1) {
			//	ssTemp = 1;
			//	ss << "v." << ii << ".vtk";
			//	infilename = ss.str();
			//}
	   else {		
	   	ssTemp = (ii)*spacing;
	   	ss << "v." << ssTemp << ".vtk";
			infilename = ss.str();
	   }
	   // open inputfile
		infile.open(infilename.c_str());
		if (!infile.is_open()) {
			cout << infilename << endl;
			cout << endl << "Failed to open file: " << infilename << endl;
			//return 0;
		}
		// -----------------------------------------------
		// open output file for 2D scan
		// -----------------------------------------------

		ss2 << "poreSpacing_" << ssTemp << ".csv";
		outfilename = ss2.str();
		outfile.open(outfilename.c_str());
		outfile << "Depth," << ssTemp << "poreSpacing," << "+-" << endl;

		// ----------------------------------------------
		// start reading input file (vtk header)
		// ----------------------------------------------
		int header = 0;
		string tmp;
		while (header < 12 && infile.good()) 
		{
			getline(infile, tmp);
			header++;
		}
		// -------------------------------------------------
		// loop over 3D space. Count solvent rich deomains
		// and count Interfaces. calculate average distance
		// between droplets
		//--------------------------------------------------
		// read input file into array3D
		for (int k = 0; k < z; k++) 
		{
			for (int j = 0; j < y; j++) 
			{
				for (int i = 0; i < x; i++) 
				{
					infile >> array3D[i][j][k];
				}
			}
		}
		// scan through array3D  scan along y
		for (int j = 0; j < y; j++) 
		{
			// --------------------
			// scan along x
			// --------------------
			for (int k = 0; k < z; k++)
			{
				for (int i= 0; i < x; i++)
				{
					testStart = array3D[i][j][k];
					if (i == 0 && testStart < 0.1) solSpace++;
					if (i == x - 1) testPoint = array3D[0][j][k];
					else testPoint = array3D[i + 1][j][k];
					if (testPoint < 0.1) solSpace++;
					if (testStart < 0.45 && testPoint >= 0.45) interface++;
					else if (testStart >= 0.45 && testPoint < 0.45) interface++;
					testStart = testPoint;
				} // end i
				if (interface == 0 && solSpace == 0) solInter = 0;
				else if (interface == 0 && solSpace != 0) solInter = 0;
				else solInter = solSpace / (0.5*interface); 	// calculate distance between bubbles
				D[k] = solInter;					// store distance in array
				solInterRun += solInter;
				solSpace = 0;
				interface = 0;
				solInter = 0.0;
			
			} // end k
			// -------------------
			// scan along z
			// -------------------
			for (int aa = 0; aa < x; aa++) {
				for (int bb = 0; bb < z; bb++) {
					testStart = array3D[aa][j][bb];
					if (bb == 0 && testStart < 0.1) solSpace++;
					if (bb == z - 1) testPoint = array3D[aa][j][0];
					else testPoint = array3D[aa][j][bb + 1];
					if (testPoint < 0.1) solSpace++;
					if (testStart < 0.45 && testPoint >= 0.45) interface++;
					else if (testStart >= 0.45 && testPoint < 0.45) interface++;
					testStart = testPoint;
				} // end bb	aka y

				if (interface == 0 && solSpace == 0) solInter = 0;
				else if (interface == 0 && solSpace != 0) interface = 0;
				else solInter = solSpace / (0.5*interface); 	// calculate distance between bubbles
				D[z + aa] = solInter;					// store distance in array
				solInterRun += D[aa + z];
				solSpace = 0;
				interface = 0;
				solInter = 0.0;			
			} // end aa aka x

			solInterAvg = solInterRun / (x + z);
			b[j] = solInterAvg;
			// standard deviation
			for (int zz = 0; zz< x + z; zz++) 
			{
				diff = b[j] - D[zz];
				diff2 = diff * diff;
				sumDiff2 += diff2;
			}
			// stdDev
			if (b[j] == 0) stdDev[j] = 0;
			else stdDev[j] = sqrt(sumDiff2 / (x + z) - 1);
			outfile << j << "," << b[j] << "," << stdDev[j] << endl;
			//	cout << " avaerage2D: " << b[k] << " stdDev: " << stdDev[k] << endl;

			sumDiff2 = 0.0;
			solInterRun = 0.0;	// end j

		} // end j
		// ---------------------------------
		// average over 3D domain
		// ---------------------------------
		double sumB = 0.0;
		double avg3D = 0.0;
		for (int j = 0; j < y; j++) 
		{
			sumB += b[j];
		}      
  
		avg3D = sumB / y;
		// standard deviation
		for (int j = 0; j < y; j++) 
		{
			diff3D = avg3D - b[j];
			diff3D_2 = diff3D * diff3D;
			sumDiff3D_2 += diff3D_2;
		}

		if (sumB == 0) stdDev3D = 0;
		else stdDev3D = sqrt(sumDiff3D_2 / (y - 1));
		outfile2 << ii << "," << avg3D << "," << stdDev3D << endl;
		infile.close();
		outfile.close();
		ss.str("");
		ss2.str("");
		ss3.str("");
		sumDiff3D_2 = 0.0;	
}
	 //close average 3D

	outfile2.close();
	// de-allocate arrays
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			delete[] array3D[i][j];
		}
	}
	delete[] array3D;
	array3D = NULL;
	delete[] b;
	b = NULL;
	delete[] stdDev;
	stdDev = NULL;
	//delete[] stdDev3D;
	//stdDev3D = NULL;
	delete[] D;
	D = NULL;
	// stop clock
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << endl << "Time :		" << elapsed_secs << endl;
}	
