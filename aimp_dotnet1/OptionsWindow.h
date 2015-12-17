namespace AIMP
{
	namespace DotNetPlugin
	{
		using namespace System::Windows;
		using namespace System::Windows::Controls;


		public ref class OptionsWindow : public Window
		{
		public:
			OptionsWindow()
			{
				Title = "AIMP DotNet Plugins";
				Initialize();
			}
		private:
			void Initialize()
			{
				ShowInTaskbar = false;
				this->WindowStyle = System::Windows::WindowStyle::None;
				this->WindowState = System::Windows::WindowState::Maximized;


				Grid^ panel = gcnew Grid();
				panel->ShowGridLines = true;

				RowDefinition^ row0 = gcnew RowDefinition();
				row0->Height = GridLength::Auto;

				RowDefinition^ row1 = gcnew RowDefinition();
				row1->Height = GridLength::Auto;

				panel->RowDefinitions->Add(row0);
				panel->RowDefinitions->Add(row1);


				Label^ formTitle = gcnew Label();
				formTitle->Content = gcnew System::String("DotNet plugins");
				panel->SetRow(formTitle, 0);


				panel->Children->Add(formTitle);

				this->Content = panel;
			}
		};
	}
}

