#include "JobList.h"

JobList* JobList::CreateJobListFromJsonFile(std::string filePath)
{
	// TODO: implementation!
	return nullptr;
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

	std::vector<JobEntity*> jobs;
	for (auto jobJson : deserialized["jobs"])
	{
		jobs.push_back(new JobEntity(jobJson["shelf_index"], jobJson["shelf_level"], jobJson["pallet_position"]));
	}

	return new JobList(jobs);
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
