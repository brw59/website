#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// Automates TM creation for base 2-10. unary is weird and different than other bases
// McAllister Scroggs Please dont judge me for the proceduralness of it... 
int main() 
{
	string nodeNames[15] = {
		"Erase C",
		"Erase Leading 0's AB", 
		"Erase Leading 0's A",
		"Erase Leading 0's B", 
		"Move AB Right", 
		"Move A Right", 
		"Move B Right", 
		"Check for Blank A or B",
		"Finish",
		"Move A Right and Erase Added 0's on B",
		"Check if Done",
		"Add 0 to B",
		"Move BC Right",
		"Move B Right",
		"Move C Right"
	};
	int base;
	cout << "What base to generate for? ";
	cin >> base;
	
	ofstream fout;
	string fileName = "TMAUTOtimes" + to_string(base) + ".jff";
	cout << fileName;
	fout.open (fileName);
	
	fout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><!--Created with JFLAP 6.4.--><structure>&#13;\n" 
	     << "\t<type>turing</type>&#13;\n"
	     << "\t<tapes>3</tapes>&#13;\n"
	     << "\t<automaton>&#13;\n"
	     << "\t\ttomaton>&#13;\n"
		  << "\t\t<!--The list of states.-->&#13;\n";
	//generate non math blocks that all bases have in common
	for (int i = 0; i < 15; i++) 
	{
		fout << "\t\t<block id=\"" << i << "\" name=\"" << nodeNames[i] <<  "\">&#13;\n"
		     << "\t\t\t<tag>Machine" << i << "</tag>&#13;\n" 
		     << "\t\t\t<x>" << i * 100 << "</x>&#13;\n"
			  << "\t\t\t<y>" << i * 100 << "</y>&#13;\n";
	  	if (i == 0)
	  		fout << "\t\t\t<initial/>&#13;\n";
	  	if (i == 8)
	  		fout << "\t\t\t<final/>&#13;\n";
		fout << "\t\t\t</block>&#13;\n";
	}
	// generate math blocks
	for (int i = 0; i < base; i++)
	{
		fout << "\t\t<block id=\"" << 15 + i << "\" name=\"Add with " << i << " Carry\">&#13;\n"
		     << "\t\t\t<tag>Machine" << 14 + i  << "</tag>&#13;\n" 
		     << "\t\t\t<x>" << i * 100  + 200<< "</x>&#13;\n"
			  << "\t\t\t<y>" << i * 100 << "</y>&#13;\n"
		     << "\t\t\t</block>&#13;\n";
	}
	fout << "\t\t<!--The list of transitions.-->&#13;\n";
	//ADD IN CODE FOR TRANSITIONS
	//common transitions
		//erase c
		for (int i = 0; i < base; i++)
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>0</from>&#13;\n"
				  << "\t\t\t<to>0</to>&#13;\n"
				  << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
				  << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"1\">S</move>&#13;\n"
				  << "\t\t\t<read tape=\"2\">~</read>&#13;\n"
				  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">S</move>&#13;\n"
				  << "\t\t\t<read tape=\"3\">" << i << "</read>&#13;\n"
				  << "\t\t\t<write tape=\"3\"></write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">R</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		}
		
		//if no input move to finish
		fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>0</from>&#13;\n"
				  << "\t\t\t<to>8</to>&#13;\n"
				  << "\t\t\t<read tape=\"1\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"1\">0</write>&#13;\n"
				  << "\t\t\t<move tape=\"1\">S</move>&#13;\n"
				  << "\t\t\t<read tape=\"2\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"2\">0</write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">S</move>&#13;\n"
				  << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">0</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		
		//if no leading 0's move to 4
		for (int j = -1; j < base; j++) {
			for (int i = -1; i < base; i++)
			{
				if (!(i == 0  || j == 0) && !(i == -1 && j == -1)) //dont want any 0's and no double empty either.
				{
					fout << "\t\t<transition>&#13;\n"
						  << "\t\t\t<from>0</from>&#13;\n"
						  << "\t\t\t<to>4</to>&#13;\n";
						  
						  if (i == -1) 
						  	fout << "\t\t\t<read tape=\"1\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"1\">~</write>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
						  	
						  if (j == -1) 
						  	fout << "\t\t\t<read tape=\"2\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"2\">" << j << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"2\">~</write>&#13;\n";
						  if (j == -1) 
						  	fout << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
						  	
						  fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
						  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
						  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
						  << "\t\t</transition>&#13;\n";
				}
			}
		}		  
		
		//from 1 to 4
		for (int j = -1; j < base; j++) {
			for (int i = -1; i < base; i++)
			{
				if (!(i == 0  || j == 0)) //dont want any 0's and no double empty is ok this time.
				{
					fout << "\t\t<transition>&#13;\n"
						  << "\t\t\t<from>1</from>&#13;\n"
						  << "\t\t\t<to>4</to>&#13;\n";
						  
						  if (i == -1) 
						  	fout << "\t\t\t<read tape=\"1\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"1\">~</write>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
						  	
						  if (j == -1) 
						  	fout << "\t\t\t<read tape=\"2\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"2\">" << j << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"2\">~</write>&#13;\n";
						  if (j == -1) 
						  	fout << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
						  	
						  fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
						  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
						  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
						  << "\t\t</transition>&#13;\n";
				}
			}
		}		  
		
		//from 2 to 4
		for (int j = -1; j < base; j++) {
			for (int i = -1; i < base; i++)
			{
				if (i != 0) //dont want any 0's on tape 1
				{
					fout << "\t\t<transition>&#13;\n"
						  << "\t\t\t<from>2</from>&#13;\n"
						  << "\t\t\t<to>4</to>&#13;\n";
						  
						  if (i == -1) 
						  	fout << "\t\t\t<read tape=\"1\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"1\">~</write>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
						  	
						  if (j == -1) 
						  	fout << "\t\t\t<read tape=\"2\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"2\">" << j << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"2\">~</write>&#13;\n";
						  if (j == -1) 
						  	fout << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
						  	
						  fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
						  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
						  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
						  << "\t\t</transition>&#13;\n";
				}
			}
		}		  
		
		//from 3 to 4
		for (int j = -1; j < base; j++) {
			for (int i = -1; i < base; i++)
			{
				if (j != 0) //dont want any 0's on tape 2
				{
					fout << "\t\t<transition>&#13;\n"
						  << "\t\t\t<from>3</from>&#13;\n"
						  << "\t\t\t<to>4</to>&#13;\n";
						  
						  if (i == -1) 
						  	fout << "\t\t\t<read tape=\"1\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"1\">~</write>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
						  	
						  if (j == -1) 
						  	fout << "\t\t\t<read tape=\"2\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"2\">" << j << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"2\">~</write>&#13;\n";
						  if (j == -1) 
						  	fout << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
						  	
						  fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
						  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
						  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
						  << "\t\t</transition>&#13;\n";
				}
			}
		}		  
		//erase leading 0's AB TRANSITION from 0
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>0</from>&#13;\n"
				  << "\t\t\t<to>1</to>&#13;\n"
				  << "\t\t\t<read tape=\"1\">0</read>&#13;\n"
				  << "\t\t\t<write tape=\"1\"></write>&#13;\n"
				  << "\t\t\t<move tape=\"1\">R</move>&#13;\n"
				  << "\t\t\t<read tape=\"2\">0</read>&#13;\n"
				  << "\t\t\t<write tape=\"2\"></write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">R</move>&#13;\n"
				  << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		
		//erase leading 0's AB TRANSITION from 1
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>1</from>&#13;\n"
				  << "\t\t\t<to>1</to>&#13;\n"
				  << "\t\t\t<read tape=\"1\">0</read>&#13;\n"
				  << "\t\t\t<write tape=\"1\"></write>&#13;\n"
				  << "\t\t\t<move tape=\"1\">R</move>&#13;\n"
				  << "\t\t\t<read tape=\"2\">0</read>&#13;\n"
				  << "\t\t\t<write tape=\"2\"></write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">R</move>&#13;\n"
				  << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		
		//erase leading 0's A TRANSITIONS to it from others
		for (int j = 0; j < 2; j++) {
			for (int i = -1; i < base; i++)
			{
				if (i != 0)
				{
					fout << "\t\t<transition>&#13;\n"
						  << "\t\t\t<from>" << j << "</from>&#13;\n"
						  << "\t\t\t<to>2</to>&#13;\n"
						  << "\t\t\t<read tape=\"1\">0</read>&#13;\n"
						  << "\t\t\t<write tape=\"1\"></write>&#13;\n"
						  << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<read tape=\"2\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"2\">" << i << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"2\">~</write>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
						  fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
						  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
						  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
						  << "\t\t</transition>&#13;\n";
				}
			}
		}
		
		//erase leading 0's A TRANSITIONS to it from self
		for (int i = -1; i < base; i++)
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>2</from>&#13;\n"
				  << "\t\t\t<to>2</to>&#13;\n"
				  << "\t\t\t<read tape=\"1\">0</read>&#13;\n"
				  << "\t\t\t<write tape=\"1\"></write>&#13;\n"
				  << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
				  if (i == -1) 
				  	fout << "\t\t\t<read tape=\"2\"></read>&#13;\n";
				  else
				   fout << "\t\t\t<read tape=\"2\">" << i << "</read>&#13;\n";
				  fout << "\t\t\t<write tape=\"2\">~</write>&#13;\n";
				  if (i == -1) 
				  	fout << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
				  else
				  	fout << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
				  fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		
		}
		
			//erase leading 0's B TRANSITIONS to it from others
		for (int j = 0; j < 2; j++) {
			for (int i = -1; i < base; i++)
			{
				if (i != 0)
				{
					fout << "\t\t<transition>&#13;\n"
						  << "\t\t\t<from>" << j << "</from>&#13;\n"
						  << "\t\t\t<to>3</to>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<read tape=\"1\"></read>&#13;\n";
						  else
						   fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n";
						  fout << "\t\t\t<write tape=\"1\">~</write>&#13;\n";
						  if (i == -1) 
						  	fout << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
						  else
						  	fout << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
					fout << "\t\t\t<read tape=\"2\">0</read>&#13;\n"
						  << "\t\t\t<write tape=\"2\"></write>&#13;\n"
						  << "\t\t\t<move tape=\"2\">R</move>&#13;\n"
						  << "\t\t\t<read tape=\"3\"></read>&#13;\n"
						  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
						  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
						  << "\t\t</transition>&#13;\n";
				}
			}
		}
		
			//erase leading 0's A TRANSITIONS to it from self
		for (int i = -1; i < base; i++)
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>3</from>&#13;\n"
				  << "\t\t\t<to>3</to>&#13;\n";
				  if (i == -1) 
				  	fout << "\t\t\t<read tape=\"1\"></read>&#13;\n";
				  else
				   fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n";
				  fout << "\t\t\t<write tape=\"1\">~</write>&#13;\n";
				  if (i == -1) 
				  	fout << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  else
				  	fout << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
			fout << "\t\t\t<read tape=\"2\">0</read>&#13;\n"
				  << "\t\t\t<write tape=\"2\"></write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">R</move>&#13;\n"
				  << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		
		}
		
		//4 to 4
		for (int j = 0; j < base; j++) {
			for (int i = 0; i < base; i++)
			{
				fout << "\t\t<transition>&#13;\n"
					  << "\t\t\t<from>4</from>&#13;\n"
					  << "\t\t\t<to>4</to>&#13;\n";
					  
				fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n"
				     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
				     << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
					  	
				fout << "\t\t\t<read tape=\"2\">" << j  << "</read>&#13;\n"
				     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
				     << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
					  	
				fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
					  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
					  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
					  << "\t\t</transition>&#13;\n";
			}
		}		  
		//4 to 5/6 and 5 to 5 and 6 to 6
		for (int i = 0; i < base; i++)
	{
			//4 to 5
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>4</from>&#13;\n"
				  << "\t\t\t<to>5</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
			//5 to 5
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>5</from>&#13;\n"
				  << "\t\t\t<to>5</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
			//4 to 6
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>4</from>&#13;\n"
				  << "\t\t\t<to>6</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\"></read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\">" << i  << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
				  
			//6 to 6
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>6</from>&#13;\n"
				  << "\t\t\t<to>6</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\"></read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\">" << i  << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		}
		
		//4/5/6 to 7
		for (int i = 0; i < 3; i++)
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>" << 4 + i<< "</from>&#13;\n"
				  << "\t\t\t<to>7</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\"></read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">L</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		}
		
		// 7 to finish(8) if has any blanks
		fout << "\t\t<transition>&#13;\n"
			  << "\t\t\t<from>7</from>&#13;\n"
			  << "\t\t\t<to>8</to>&#13;\n";
			  
		fout << "\t\t\t<read tape=\"1\"></read>&#13;\n"
		     << "\t\t\t<write tape=\"1\">0</write>&#13;\n"
		     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
		     << "\t\t\t<write tape=\"2\">0</write>&#13;\n"
		     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
			  << "\t\t\t<write tape=\"3\">0</write>&#13;\n"
			  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
			  << "\t\t</transition>&#13;\n";
		//more
		fout << "\t\t<transition>&#13;\n"
			  << "\t\t\t<from>7</from>&#13;\n"
			  << "\t\t\t<to>8</to>&#13;\n";
			  
		fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
		     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
		     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
		     << "\t\t\t<write tape=\"2\">0</write>&#13;\n"
		     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
			  << "\t\t\t<write tape=\"3\">0</write>&#13;\n"
			  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
			  << "\t\t</transition>&#13;\n";
		//last one for this
		fout << "\t\t<transition>&#13;\n"
			  << "\t\t\t<from>7</from>&#13;\n"
			  << "\t\t\t<to>8</to>&#13;\n";
			  
		fout << "\t\t\t<read tape=\"1\"></read>&#13;\n"
		     << "\t\t\t<write tape=\"1\">0</write>&#13;\n"
		     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"2\">~</read>&#13;\n"
		     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
		     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
			  << "\t\t\t<write tape=\"3\">0</write>&#13;\n"
			  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
			  << "\t\t</transition>&#13;\n";
	// END OF PREPARATION PHASE******************************************
	// START OF COMMON MATH AND CLEANUP**********************************
	// from erase (9) to finish (8) 
		fout << "\t\t<transition>&#13;\n"
			  << "\t\t\t<from>9</from>&#13;\n"
			  << "\t\t\t<to>8</to>&#13;\n";
			  
		fout << "\t\t\t<read tape=\"1\"></read>&#13;\n"
		     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
		     << "\t\t\t<move tape=\"1\">L</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"2\">~</read>&#13;\n"
		     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
		     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"3\">~</read>&#13;\n"
			  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
			  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
			  << "\t\t</transition>&#13;\n";
	// erase to erase leading 0s (9
		for (int i = 0; i < base; i++)
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>9</from>&#13;\n"
				  << "\t\t\t<to>9</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">" << i << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\">0</read>&#13;\n"
			     << "\t\t\t<write tape=\"2\"></write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\">~</read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		}
	// from check if done (10) to erase leading 0s (9)
		fout << "\t\t<transition>&#13;\n"
			  << "\t\t\t<from>10</from>&#13;\n"
			  << "\t\t\t<to>9</to>&#13;\n";
			  
		fout << "\t\t\t<read tape=\"1\"></read>&#13;\n"
		     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
		     << "\t\t\t<move tape=\"1\">R</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"2\">~</read>&#13;\n"
		     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
		     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"3\">~</read>&#13;\n"
			  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
			  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
			  << "\t\t</transition>&#13;\n";
	// move to add 0 to b from 7 and 10
		for (int i = 0; i < 2; i++)
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>" << 7 + (i * 3) << "</from>&#13;\n"
				  << "\t\t\t<to>11</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">0</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\">~</read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\">~</read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		}
	// move from add 0 to b to check if done (10)
		fout << "\t\t<transition>&#13;\n"
			  << "\t\t\t<from>11</from>&#13;\n"
			  << "\t\t\t<to>10</to>&#13;\n";
			  
		fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
		     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
		     << "\t\t\t<move tape=\"1\">L</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
		     << "\t\t\t<write tape=\"2\">0</write>&#13;\n"
		     << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
			  	
		fout << "\t\t\t<read tape=\"3\">~</read>&#13;\n"
			  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
			  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
			  << "\t\t</transition>&#13;\n";
			  
	//12 to 12
		for (int j = 0; j < base; j++) {
			for (int i = 0; i < base; i++)
			{
				fout << "\t\t<transition>&#13;\n"
					  << "\t\t\t<from>12</from>&#13;\n"
					  << "\t\t\t<to>12</to>&#13;\n";
					  
				fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
				     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
				     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
					  	
				fout << "\t\t\t<read tape=\"2\">" << i  << "</read>&#13;\n"
				     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
				     << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
					  	
				fout << "\t\t\t<read tape=\"3\">" << j  << "</read>&#13;\n"
					  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
					  << "\t\t\t<move tape=\"3\">R</move>&#13;\n"
					  << "\t\t</transition>&#13;\n";
			}
		}		  
	//12 to 13/14 and 13 to 13 and 14 to 15
		for (int i = 0; i < base; i++)
		{
			//12 to 13
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>12</from>&#13;\n"
				  << "\t\t\t<to>13</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\">" << i << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
			//12 to 14
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>12</from>&#13;\n"
				  << "\t\t\t<to>14</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
				  	  	
			fout << "\t\t\t<read tape=\"3\">" << i << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"3\">R</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
			//13 to 13
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>13</from>&#13;\n"
				  << "\t\t\t<to>13</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\">" << i << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"3\">S</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
				  
			//6 to 6
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>14</from>&#13;\n"
				  << "\t\t\t<to>14</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
				  
				  	  	
			fout << "\t\t\t<read tape=\"3\">" << i << "</read>&#13;\n"
			     << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"3\">R</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		}
	// move from 12/13/14 to check if done (10)
		for (int i = 0; i < 3; i++)
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>" << 12 + i << "</from>&#13;\n"
				  << "\t\t\t<to>10</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">L</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"2\">0</write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">S</move>&#13;\n";
				  
				  	  	
			fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
			     << "\t\t\t<write tape=\"3\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"3\">L</move>&#13;\n"
				  << "\t\t</transition>&#13;\n";
		}
	// DONE WITH ALL NON MATH TRANSITIONS********************************
	
		for(int a = 1; a < base; a++) { //multiplier starts on 1 as 0 does nothing
			for(int b = 0; b < base; b++) { //multiplicand 0 is useful here
				for(int c = 0; c < base; c++) { // product...
					for(int d = 0; d < base; d++) { // the prior carry
						int pro = a * b; // product
						int sum = pro + c + d; // sum (product + sum + carry)
						int car = 0; // the carry created
						while (sum > base - 1) { //base - 1 equals largest number in language
							sum -= base; // chop of the extra
							car++; // and store extra as a carry
						} 
						if (d == 0) // when in the no carry state the transitions are the same as from check if AB empty and check if done states
						{
							if (c == 0) {// this case is for the blank possiblity when the sum is empty 
								fout << "\t\t<transition>&#13;\n"
									  << "\t\t\t<from>7</from>&#13;\n"
									  << "\t\t\t<to>" << car + 15 << "</to>&#13;\n";
									  
								fout << "\t\t\t<read tape=\"1\">" << a << "</read>&#13;\n"
								     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
								     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
									  	
								fout << "\t\t\t<read tape=\"2\">" << b << "</read>&#13;\n"
									  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
									  << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
									  	  	
								fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
								     << "\t\t\t<write tape=\"3\">" << sum << "</write>&#13;\n"
								     << "\t\t\t<move tape=\"3\">L</move>&#13;\n"
									  << "\t\t</transition>&#13;\n";
									  
								fout << "\t\t<transition>&#13;\n"
									  << "\t\t\t<from>10</from>&#13;\n"
									  << "\t\t\t<to>" << car + 15<< "</to>&#13;\n";
									  
								fout << "\t\t\t<read tape=\"1\">" << a << "</read>&#13;\n"
								     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
								     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
									  	
								fout << "\t\t\t<read tape=\"2\">" << b << "</read>&#13;\n"
									  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
									  << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
									  	  	
								fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
								     << "\t\t\t<write tape=\"3\">" << sum << "</write>&#13;\n"
								     << "\t\t\t<move tape=\"3\">L</move>&#13;\n"
									  << "\t\t</transition>&#13;\n";
							}
							
							fout << "\t\t<transition>&#13;\n"
								  << "\t\t\t<from>7</from>&#13;\n"
								  << "\t\t\t<to>" << car + 15 << "</to>&#13;\n";
								  
							fout << "\t\t\t<read tape=\"1\">" << a << "</read>&#13;\n"
							     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
							     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
								  	
							fout << "\t\t\t<read tape=\"2\">" << b << "</read>&#13;\n"
								  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
								  << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
								  	  	
							fout << "\t\t\t<read tape=\"3\">" << c << "</read>&#13;\n"
							     << "\t\t\t<write tape=\"3\">" << sum << "</write>&#13;\n"
							     << "\t\t\t<move tape=\"3\">L</move>&#13;\n"
								  << "\t\t</transition>&#13;\n";
								  
							fout << "\t\t<transition>&#13;\n"
								  << "\t\t\t<from>10</from>&#13;\n"
								  << "\t\t\t<to>" << car + 15 << "</to>&#13;\n";
								  
							fout << "\t\t\t<read tape=\"1\">" << a << "</read>&#13;\n"
							     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
							     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
								  	
							fout << "\t\t\t<read tape=\"2\">" << b << "</read>&#13;\n"
								  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
								  << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
								  	  	
							fout << "\t\t\t<read tape=\"3\">" << c << "</read>&#13;\n"
							     << "\t\t\t<write tape=\"3\">" << sum << "</write>&#13;\n"
							     << "\t\t\t<move tape=\"3\">L</move>&#13;\n"
								  << "\t\t</transition>&#13;\n";
						}
						if (c == 0) {// this case is for the blank possiblity when the sum is empty 
							fout << "\t\t<transition>&#13;\n"
								  << "\t\t\t<from>" << d + 15 << "</from>&#13;\n"
								  << "\t\t\t<to>" << car + 15<< "</to>&#13;\n";
								  
							fout << "\t\t\t<read tape=\"1\">" << a << "</read>&#13;\n"
							     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
							     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
								  	
							fout << "\t\t\t<read tape=\"2\">" << b << "</read>&#13;\n"
								  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
								  << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
								  	  	
							fout << "\t\t\t<read tape=\"3\"></read>&#13;\n"
							     << "\t\t\t<write tape=\"3\">" << sum << "</write>&#13;\n"
							     << "\t\t\t<move tape=\"3\">L</move>&#13;\n"
								  << "\t\t</transition>&#13;\n";
						}
						
						fout << "\t\t<transition>&#13;\n"
							  << "\t\t\t<from>" << d + 15 << "</from>&#13;\n"
							  << "\t\t\t<to>" << car + 15<< "</to>&#13;\n";
							  
						fout << "\t\t\t<read tape=\"1\">" << a << "</read>&#13;\n"
						     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
						     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
							  	
						fout << "\t\t\t<read tape=\"2\">" << b << "</read>&#13;\n"
							  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
							  << "\t\t\t<move tape=\"2\">L</move>&#13;\n";
							  	  	
						fout << "\t\t\t<read tape=\"3\">" << c << "</read>&#13;\n"
						     << "\t\t\t<write tape=\"3\">" << sum << "</write>&#13;\n"
						     << "\t\t\t<move tape=\"3\">L</move>&#13;\n"
							  << "\t\t</transition>&#13;\n";
						}
					}
				}
			}	
	//transitions from add states to move BC Right (12)
		for ( int i = 0; i < base; i++) 
		{
			fout << "\t\t<transition>&#13;\n"
				  << "\t\t\t<from>" << i + 15 << "</from>&#13;\n"
				  << "\t\t\t<to>12</to>&#13;\n";
				  
			fout << "\t\t\t<read tape=\"1\">~</read>&#13;\n"
			     << "\t\t\t<write tape=\"1\">~</write>&#13;\n"
			     << "\t\t\t<move tape=\"1\">S</move>&#13;\n";
				  	
			fout << "\t\t\t<read tape=\"2\"></read>&#13;\n"
				  << "\t\t\t<write tape=\"2\">~</write>&#13;\n"
				  << "\t\t\t<move tape=\"2\">R</move>&#13;\n";
			if (i == 0)
			{	  	  	
				fout << "\t\t\t<read tape=\"3\">~</read>&#13;\n"
				     << "\t\t\t<write tape=\"3\"></write>&#13;\n"
				     << "\t\t\t<move tape=\"3\">R</move>&#13;\n"
					  << "\t\t</transition>&#13;\n";
			}
			else
			{	  	  	
				fout << "\t\t\t<read tape=\"3\">~</read>&#13;\n"
				     << "\t\t\t<write tape=\"3\">" << i << "</write>&#13;\n"
				     << "\t\t\t<move tape=\"3\">R</move>&#13;\n"
					  << "\t\t</transition>&#13;\n";
			}
		}
		fout << "\t\t<!--The list of automata-->&#13;\n";
		for (int i = 0; i < 14 + base; i++) 
		{
			fout << "\t\t<Machine" << i << "/>&#13;\n";
		}
		fout << "\t</automaton>&#13;\n"
		     << "</structure>";
	fout.close();
	return 0;
}
