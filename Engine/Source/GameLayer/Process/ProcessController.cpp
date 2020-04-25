#include "ProcessController.h"

using halo::ProcessController;

ProcessController::ProcessController()
{
	
}

ProcessController::~ProcessController()
{
	AbortAllProcesses();
}

void halo::ProcessController::UpdateProcesses(float deltaSeconds)
{
	size_t processIndex = 0;
	while (processIndex < m_processes.size())
	{
		// Only going to increment the index when we don't remove a process
		auto pProcess = m_processes[processIndex];

		if (pProcess->GetState() == IProcess::State::kRunning)
		{
			pProcess->Update(deltaSeconds);
		}
		else if (pProcess->GetState() == IProcess::State::kUninitialized)
		{
			if (pProcess->PostInit())
			{
				pProcess->Resume();
			}
			else
			{
				// remove it !
				m_processes.erase(m_processes.begin() + processIndex);
				continue;
			}
		}
		else if (pProcess->IsDead())
		{
			IProcess::State state = pProcess->GetState();
			if (state == IProcess::State::kSucceeded)
			{
				// Add a child if there is any
				pProcess->OnSucceed();
				auto pChild = pProcess->RemoveChild();
				if (pChild)
					m_processes.emplace_back(pChild);
			}
			else if (state == IProcess::State::kFailed)
			{
				pProcess->OnFailure();
			}
			else if (state == IProcess::State::kAborted)
			{
				pProcess->OnAbort();
			}

			pProcess->Reset();
			// remove it
			m_processes.erase(m_processes.begin() + processIndex);
			continue;
		}

		++processIndex;
	}
}

void halo::ProcessController::AbortAllProcesses()
{
	for (auto& proc : m_processes)
	{
		if (proc->IsAlive())
		{
			proc->Abort();
			proc->OnAbort();
		}
	}

	m_processes.clear();
}
