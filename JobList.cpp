#include "JobList.h"

JobList* JobList::CreateJobListFromJsonFile(std::string filePath)
{
}

JobList* JobList::CreateJobListFromJsonString(std::string json)
{
}

std::vector<Operation*> JobList::GenerateOperations()
{
	std::vector<Operation*> result;// = std::vector<Operation*>(1000);

	for (std::vector<JobEntity*>::value_type job : this->jobs)
	{
		std::vector<Operation*> jobOperation = job->GenerateOperations();
		result.insert(result.end(), jobOperation.begin(), jobOperation.end());
	}

	return result;
}
