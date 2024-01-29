#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>

struct cluster {
	std::string clusterName;
	int lineNumber;
};

std::vector<std::string> clusters;
std::vector<cluster> clusterFind;

int selected = 0;
int selectedRegion = 0;
int selectedClearSettings = 0;

int main()
{

Restart:
	clusters.clear();
	system("title Wot Blitz Cluster Selector");

	std::cout << "Select region: EU, RU (0, 1): ";
	try {
		std::cin >> selectedRegion;
	}
	catch (...)
	{
		std::cout << "Unknown region!" << std::endl;
		Sleep(2000);
		goto Restart;
	}

	if (selectedRegion == 0)
	{
		std::cout << "Select cluster (0, 1, 2, 3, 4): ";
		clusters = { "login0.wotblitz.eu", "login1.wotblitz.eu", "login2.wotblitz.eu", "login3.wotblitz.eu", "login4.wotblitz.eu" };
	}
	else if(selectedRegion == 1)
	{
		std::cout << "Select cluster (0, 1, 2, 3, 4, 5): ";
		clusters = { "login0.tanksblitz.ru", "login1.tanksblitz.ru", "login2.tanksblitz.ru", "login3.tanksblitz.ru", "login4.tanksblitz.ru", "login5.tanksblitz.ru"};
	}
	else
	{
		std::cout << "Unknown region!" << std::endl;
		Sleep(2000);
		goto Restart;
	}

	try {
		std::cin >> selected;
	}
	catch (...)
	{
		std::cout << "Unknown cluster!" << std::endl;
		Sleep(2000);
		goto Restart;
	}

	if (0 > selected || selected > clusters.size() - 1)
	{
		std::cout << "Unknown cluster!" << std::endl;
		Sleep(2000);
		goto Restart;
	}

	std::cout << "Clear settings? (YES = 1, NO = 0): ";
	try {
		std::cin >> selectedClearSettings;
	}
	catch (...)
	{
		std::cout << "Unknown choose !" << std::endl;
		Sleep(2000);
		goto Restart;
	}


	if (selectedClearSettings < 0 || selectedClearSettings > 1)
	{
		std::cout << "Unknown choose!" << std::endl;
		Sleep(2000);
		goto Restart;
	}

	std::string HostsPath = "C:\\Windows\\System32\\drivers\\etc\\hosts";

	std::fstream fstream(HostsPath, std::ios::out | std::ios::in);

	if (!fstream.is_open())
	{
		std::cout << "Failed to open file!" << std::endl;
		Sleep(5000);
		return 1;
	}

	std::vector<std::string> hosts;
	std::string line;

	while (fstream)
	{
		std::getline(fstream, line);
		hosts.push_back(line + "\n");
	}

	for (int i = 0; i < hosts.size(); i++)
	{
		for(int j = 0; j < clusters.size(); j++)
		{
			if (hosts[i].find(clusters[j]) != std::string::npos)
				clusterFind.push_back({  clusters[j], i });
		}
	}
	
	std::string out;
	if (clusterFind.size() != 0)
	{
		for (int i = 0; i < clusterFind.size(); i++)
		{
			if (selectedClearSettings == 0)
			{
				if (selected == i)
				{
					hosts[clusterFind[i].lineNumber] = "#127.0.0.1 " + clusters[i] + "\n";

				}
				else
				{
					hosts[clusterFind[i].lineNumber] = "127.0.0.1 " + clusters[i] + "\n";
				}
			}
			else 
			{
				hosts[clusterFind[i].lineNumber] = "";
			}
			
		}
	}
	else 
	{
		
		for (int i = 0; i < clusters.size(); i++)
		{
			if (selected == i)
			{
				hosts.push_back("#127.0.0.1 " + clusters[i] + "\n");
			}
			else 
			{
				hosts.push_back("127.0.0.1 " + clusters[i] + "\n");
			}
		}
		
	}
	for (int i = 0; i < hosts.size(); i++)
	{
		if(hosts[i] != " " && !hosts[i].empty() && hosts[i] != "\n")
			out += hosts[i];
	}

	fstream.close();

	std::ofstream ofstream(HostsPath);

	if (!ofstream.is_open())
	{
		std::cout << "Failed to open file!" << std::endl;
		Sleep(5000);
		return 1;
	}

	ofstream << out;

	ofstream.close();
	

	if (selectedClearSettings == 0)
	{
		std::cout << "Selected!" << std::endl;
	}
	else {
		std::cout << "Cleared!" << std::endl;
	}
	Sleep(5000);
	return 0;
}

