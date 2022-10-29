#pragma once

namespace CDR {

	int Main();

	class Engine final
	{
		friend int Main();

		static inline Engine* sEngine;

		bool mRunning = true;

		Engine();
		~Engine();

		void Loop();

	public:
		static inline Engine& Get() { return *sEngine; }

		void Quit();
	};

}