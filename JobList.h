﻿#pragma once
#include <utility>
#include "JobEntity.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JobList
{
private:
	std::vector<JobEntity*> jobs;
	int number_of_shelves;

	explicit JobList(std::vector<JobEntity*> jobs)
		: jobs(std::move(jobs)), number_of_shelves(0)
	{
	}

public:	
	static JobList* CreateJobListFromJsonFile(std::string filePath);
	static JobList* CreateJobListFromJsonString(std::string jsonString);

	std::vector<Operation*> GenerateOperations();

	int get_number_of_shelves() const
	{
		return number_of_shelves;
	}
};
