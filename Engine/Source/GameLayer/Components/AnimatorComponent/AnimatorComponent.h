#pragma once
// \file AnimatorComponent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IComponent.h"
#include <SDL/SDL_rect.h>
#include <unordered_map>
#include <string>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \struct Animation Sequence 
	// TODO: struct Purpose 
	struct AnimationSequence
	{
		std::string m_name;
		int m_firstFrame;
		int m_lastFrame;

		AnimationSequence() = default;
		~AnimationSequence() = default;
	};

	class RenderableComponent;

	// \class AnimatorComponent 
	// TODO: Class Purpose 
	class AnimatorComponent
		: public IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		static const ID m_sComponentID;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		AnimatorComponent() = default;
		AnimatorComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName);

		// Default Destructor 
		virtual ~AnimatorComponent();

		virtual bool Init(tinyxml2::XMLElement* pData) final override;
		ID GetID() const final override;

		// Functions
		void UpdateFrameNumber();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		RenderableComponent* m_pRenderable;

		// spritesheet column
		int m_spriteSheetColumns;

		// index of the current frame
		int m_currentFrameNumber;

		// current Animation sequence name
		const char* m_currentSequenceName;

		// map of this object's animation sequence
		std::unordered_map<std::string, halo::AnimationSequence> m_allAnimations;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// set which action animation to play
		void PlayAnimation(const char* sequenceName);
		void UpdateSourceTransform();
		int CurrentFrame() const { return m_currentFrameNumber; }
	};
}