#pragma once
// \file ProcessController.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>
#include <vector>

#include <GameLayer/Process/IProcess.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class ProcessController 
	// TODO: Class Purpose 
	class ProcessController
	{
	public:
		// Alias
		using SharedProcess = std::shared_ptr<IProcess>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		ProcessController();

		// Default Destructor 
		~ProcessController();

		void UpdateProcesses(float deltaSeconds);
		void AttachProcess(SharedProcess pProcess) { m_processes.emplace_back(pProcess); }
		void AbortAllProcesses();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::vector<SharedProcess> m_processes;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}