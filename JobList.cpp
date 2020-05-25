#include "JobList.h"

JobList* JobList::CreateJobListFromJsonFile(std::string filePath)
{
	// TODO: implementation!

	std::ifstream t(filePath);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	
	return JobList::CreateJobListFromJsonString(str);
}

JobList* JobList::CreateJobListFromJsonString(std::string jsonString)
{
	json deserialized;
	try
	{
		deserialized = json::parse(jsonString);
	}
	catch (json::parse_error& e)
	{
		std::cerr << "Exception occurred when parsing json:" << std::endl;
		std::cerr << e.what() << std::endl;
		exit(-1);
	}

	int max_shelf_index = 0;
	std::vector<JobEntity*> jobs;

	// Go to start position
	jobs.push_back(new JobEntity(-1, -1, -1));

	for (auto jobJson : deserialized["jobs"])
	{
		const int shelf_index = jobJson["shelf_index"];
		if (shelf_index > max_shelf_index)
		{
			max_shelf_index = shelf_index;
		}
		
		jobs.push_back(new JobEntity(shelf_index, jobJson["shelf_level"], jobJson["pallet_position"]));
	}

	return new JobList(jobs, max_shelf_index + 1);
}

std::vector<Operation*> JobList::GenerateOperations()
{
	std::vector<Operation*> result;

	for (std::vector<JobEntity*>::value_type job : this->jobs)
	{
		std::vector<Operation*> jobOperation = job->GenerateOperations();
		result.insert(result.end(), jobOperation.begin(), jobOperation.end());
	}

	return result;
}
