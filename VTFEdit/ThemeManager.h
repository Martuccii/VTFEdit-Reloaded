/*
 * VTFEdit
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::ComponentModel;

namespace VTFEdit
{
	public enum class ThemeType
	{
		Light,
		Dark
	};

	public ref class CThemeManager
	{
	private:
		static ThemeType currentTheme = ThemeType::Light;
		static String^ configFile;

	public:
		// Theme colors for light mode
		static property Color LightBackColor { Color get() { return Color::FromArgb(240, 240, 240); } }
		static property Color LightForeColor { Color get() { return Color::FromArgb(0, 0, 0); } }
		static property Color LightControlBackColor { Color get() { return Color::FromArgb(255, 255, 255); } }
		static property Color LightControlForeColor { Color get() { return Color::FromArgb(0, 0, 0); } }
		static property Color LightMenuBackColor { Color get() { return Color::FromArgb(240, 240, 240); } }
		static property Color LightMenuForeColor { Color get() { return Color::FromArgb(0, 0, 0); } }
		static property Color LightToolStripBackColor { Color get() { return Color::FromArgb(240, 240, 240); } }
		static property Color LightToolStripForeColor { Color get() { return Color::FromArgb(0, 0, 0); } }
		static property Color LightStatusBarBackColor { Color get() { return Color::FromArgb(240, 240, 240); } }
		static property Color LightStatusBarForeColor { Color get() { return Color::FromArgb(0, 0, 0); } }

		// Theme colors for dark mode
		static property Color DarkBackColor { Color get() { return Color::FromArgb(32, 32, 32); } }
		static property Color DarkForeColor { Color get() { return Color::FromArgb(255, 255, 255); } }
		static property Color DarkControlBackColor { Color get() { return Color::FromArgb(48, 48, 48); } }
		static property Color DarkControlForeColor { Color get() { return Color::FromArgb(255, 255, 255); } }
		static property Color DarkMenuBackColor { Color get() { return Color::FromArgb(48, 48, 48); } }
		static property Color DarkMenuForeColor { Color get() { return Color::FromArgb(255, 255, 255); } }
		static property Color DarkToolStripBackColor { Color get() { return Color::FromArgb(48, 48, 48); } }
		static property Color DarkToolStripForeColor { Color get() { return Color::FromArgb(255, 255, 255); } }
		static property Color DarkStatusBarBackColor { Color get() { return Color::FromArgb(48, 48, 48); } }
		static property Color DarkStatusBarForeColor { Color get() { return Color::FromArgb(255, 255, 255); } }

		// Current theme properties
		static property Color BackColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkBackColor : LightBackColor; 
			} 
		}

		static property Color ForeColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkForeColor : LightForeColor; 
			} 
		}

		static property Color ControlBackColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkControlBackColor : LightControlBackColor; 
			} 
		}

		static property Color ControlForeColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkControlForeColor : LightControlForeColor; 
			} 
		}

		static property Color MenuBackColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkMenuBackColor : LightMenuBackColor; 
			} 
		}

		static property Color MenuForeColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkMenuForeColor : LightMenuForeColor; 
			} 
		}

		static property Color ToolStripBackColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkToolStripBackColor : LightToolStripBackColor; 
			} 
		}

		static property Color ToolStripForeColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkToolStripForeColor : LightToolStripForeColor; 
			} 
		}

		static property Color StatusBarBackColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkStatusBarBackColor : LightStatusBarBackColor; 
			} 
		}

		static property Color StatusBarForeColor 
		{ 
			Color get() 
			{ 
				return (currentTheme == ThemeType::Dark) ? DarkStatusBarForeColor : LightStatusBarForeColor; 
			} 
		}

		// Current theme
		static property ThemeType CurrentTheme
		{
			ThemeType get() { return currentTheme; }
			void set(ThemeType theme) 
			{ 
				currentTheme = theme;
				SaveTheme();
			}
		}

		// Initialize the theme manager
		static void Initialize(String^ configPath)
		{
			configFile = configPath;
			LoadTheme();
		}

		// Apply theme to a form and all its controls
		static void ApplyTheme(Form^ form)
		{
			if (form == nullptr) return;

			// Apply to main form
			form->BackColor = BackColor;
			form->ForeColor = ForeColor;

			// Apply to all controls recursively
			ApplyThemeToControl(form);
			
			// Force refresh all controls to ensure theme is applied
			ForceRefresh(form);
			
			// Ensure controls maintain their functionality after theme application
			EnsureControlFunctionality(form);
			
			// Force a complete repaint of the form and all controls
			form->Refresh();
			Application::DoEvents();
			
			// Additional force update for problematic controls
			ForceUpdateAllControls(form);
			
			// Final force update after a brief delay to catch any remaining controls
			FinalThemeUpdate(form);
			
			// Additional specific update for Image section controls
			ForceUpdateImageSectionGlobally(form);
		}

		// Force refresh of all controls to ensure theme is applied
		static void ForceRefresh(Form^ form)
		{
			if (form == nullptr) return;

			// Force the form to redraw
			form->Invalidate();
			form->Update();

			// Force all controls to redraw
			ForceRefreshControl(form);
			
			// Force a complete repaint of the entire form
			form->Refresh();
			form->Update();
		}
		
		// Global force update for Image section controls
		static void ForceUpdateImageSectionGlobally(Form^ form)
		{
			if (form == nullptr) return;
			
			// Find and force update all Image section controls globally
			ForceUpdateImageSectionGloballyRecursive(form);
			
			// Force one more complete update
			form->Invalidate();
			form->Update();
			form->Refresh();
		}
		
		// Recursively find and update Image section controls globally
		static void ForceUpdateImageSectionGloballyRecursive(Control^ control)
		{
			if (control == nullptr) return;
			
			// Check if this control is part of the Image section
			if (!String::IsNullOrEmpty(control->Name))
			{
				String^ controlName = control->Name->ToLower();
				if (controlName->Contains("image") || controlName->Contains("flags") || 
					controlName->Contains("grp") || controlName->Contains("panel") ||
					controlName->Contains("lbl") || controlName->Contains("num") ||
					controlName->Contains("btn") || controlName->Contains("check"))
				{
					// Force these controls to use exact theme colors
					if (CurrentTheme == ThemeType::Dark)
					{
						control->BackColor = Color::FromArgb(48, 48, 48); // Dark background
						control->ForeColor = Color::White; // White text
					}
					else
					{
						control->BackColor = Color::FromArgb(255, 255, 255); // Light background
						control->ForeColor = Color::Black; // Black text
					}
					
					// Force immediate redraw
					control->Invalidate();
					control->Update();
					control->Refresh();
					
					// Force update all child controls
					for each (Control^ child in control->Controls)
					{
						if (child != nullptr)
						{
							// Force child controls to use theme colors
							if (CurrentTheme == ThemeType::Dark)
							{
								child->BackColor = Color::FromArgb(48, 48, 48); // Dark background
								child->ForeColor = Color::White; // White text
							}
							else
							{
								child->BackColor = Color::FromArgb(255, 255, 255); // Light background
								child->ForeColor = Color::Black; // Black text
							}
							
							// Force immediate redraw
							child->Invalidate();
							child->Update();
						}
					}
				}
			}
			
			// Recursively process all child controls
			for each (Control^ child in control->Controls)
			{
				ForceUpdateImageSectionGloballyRecursive(child);
			}
		}

		// Recursively force refresh all controls
		static void ForceRefreshControl(Control^ control)
		{
			if (control == nullptr) return;

			// Force this control to redraw
			control->Invalidate();
			control->Update();

			// Force all child controls to redraw
			for each (Control^ child in control->Controls)
			{
				ForceRefreshControl(child);
			}
		}
		
		// Ensure controls maintain their functionality after theme application
		static void EnsureControlFunctionality(Form^ form)
		{
			if (form == nullptr) return;
			
			// Ensure all controls maintain their event handlers and properties
			EnsureControlFunctionalityRecursive(form);
			
			// Force update of specific problematic controls that might not update properly
			ForceUpdateSpecificControls(form);
		}
		
		// Recursively ensure control functionality
		static void EnsureControlFunctionalityRecursive(Control^ control)
		{
			if (control == nullptr) return;
			
			// For ToolStrip controls, ensure they maintain their functionality
			if (control->GetType() == ToolStrip::typeid)
			{
				ToolStrip^ toolStrip = dynamic_cast<ToolStrip^>(control);
				if (toolStrip != nullptr)
				{
					// Ensure the ToolStrip maintains its functionality
					toolStrip->Renderer = gcnew ToolStripProfessionalRenderer();
				}
			}
			
			// Recursively process all child controls
			for each (Control^ child in control->Controls)
			{
				EnsureControlFunctionalityRecursive(child);
			}
		}
		
		// Force update of specific problematic controls that might not update properly
		static void ForceUpdateSpecificControls(Form^ form)
		{
			if (form == nullptr) return;
			
			// Force update of all controls that might have hardcoded colors
			ForceUpdateSpecificControlsRecursive(form);
		}
		
		// Recursively force update specific controls
		static void ForceUpdateSpecificControlsRecursive(Control^ control)
		{
			if (control == nullptr) return;
			
			// Force update of specific control types that commonly have theme issues
			if (control->GetType() == Panel::typeid || 
				control->GetType() == GroupBox::typeid ||
				control->GetType() == TabPage::typeid)
			{
				// Force these controls to update their appearance
				control->BackColor = (CurrentTheme == ThemeType::Dark) ? DarkControlBackColor : LightControlBackColor;
				control->ForeColor = (CurrentTheme == ThemeType::Dark) ? DarkControlForeColor : LightControlForeColor;
				
				// Force immediate redraw
				control->Invalidate();
				control->Update();
			}
			
			// Special handling for controls that might have hardcoded colors
			// Check if the control name contains specific keywords that might indicate theme-sensitive areas
			if (!String::IsNullOrEmpty(control->Name))
			{
				String^ controlName = control->Name->ToLower();
				if (controlName->Contains("image") || controlName->Contains("panel") || 
					controlName->Contains("group") || controlName->Contains("tab"))
				{
					// Force these controls to use the current theme colors
					control->BackColor = (CurrentTheme == ThemeType::Dark) ? DarkControlBackColor : LightControlBackColor;
					control->ForeColor = (CurrentTheme == ThemeType::Dark) ? DarkControlForeColor : LightControlForeColor;
					
					// Force immediate redraw
					control->Invalidate();
					control->Update();
				}
			}
			
			// Special handling for Image section controls
			ForceUpdateImageSectionControls(control);
			
			// Recursively process all child controls
			for each (Control^ child in control->Controls)
			{
				ForceUpdateSpecificControlsRecursive(child);
			}
		}
		
		// Special handling for Image section controls
		static void ForceUpdateImageSectionControls(Control^ control)
		{
			if (control == nullptr) return;
			
			// Check if this is the main Image group box
			if (!String::IsNullOrEmpty(control->Name) && control->Name->ToLower()->Contains("grpimage"))
			{
				// Force the Image group box to use theme colors
				if (CurrentTheme == ThemeType::Dark)
				{
					control->BackColor = Color::FromArgb(48, 48, 48); // Dark background
					control->ForeColor = Color::White; // White text
				}
				else
				{
					control->BackColor = Color::FromArgb(255, 255, 255); // Light background
					control->ForeColor = Color::Black; // Black text
				}
				
				// Force immediate redraw
				control->Invalidate();
				control->Update();
				
				// Force update all child controls in the Image section
				ForceUpdateImageChildControls(control);
			}
			
			// Also check for Flags section and other problematic areas
			if (!String::IsNullOrEmpty(control->Name))
			{
				String^ controlName = control->Name->ToLower();
				if (controlName->Contains("flags") || controlName->Contains("grpflags") ||
					controlName->Contains("check") || controlName->Contains("checkbox"))
				{
					// Force these controls to use theme colors
					if (CurrentTheme == ThemeType::Dark)
					{
						control->BackColor = Color::FromArgb(48, 48, 48); // Dark background
						control->ForeColor = Color::White; // White text
					}
					else
					{
						control->BackColor = Color::FromArgb(255, 255, 255); // Light background
						control->ForeColor = Color::Black; // Black text
					}
					
					// Force immediate redraw
					control->Invalidate();
					control->Update();
					
					// Force update all child controls
					ForceUpdateImageChildControls(control);
				}
			}
		}
		
		// Force update all child controls in the Image section
		static void ForceUpdateImageChildControls(Control^ control)
		{
			if (control == nullptr) return;
			
			// Update all child controls with specific theme colors
			for each (Control^ child in control->Controls)
			{
				if (child == nullptr) continue;
				
				// Force update based on control type
				if (child->GetType() == Label::typeid)
				{
					// Labels should inherit parent background but have theme-appropriate text color
					if (CurrentTheme == ThemeType::Dark)
					{
						child->BackColor = Color::Transparent; // Transparent background to show parent
						child->ForeColor = Color::White; // White text
					}
					else
					{
						child->BackColor = Color::Transparent; // Transparent background to show parent
						child->ForeColor = Color::Black; // Black text
					}
				}
				else if (child->GetType() == NumericUpDown::typeid)
				{
					// NumericUpDown controls need specific colors
					if (CurrentTheme == ThemeType::Dark)
					{
						child->BackColor = Color::FromArgb(64, 64, 64); // Darker background for input
						child->ForeColor = Color::White; // White text
					}
					else
					{
						child->BackColor = Color::FromArgb(240, 240, 240); // Light background for input
						child->ForeColor = Color::Black; // Black text
					}
				}
				else if (child->GetType() == Button::typeid)
				{
					// Buttons need specific colors
					if (CurrentTheme == ThemeType::Dark)
					{
						child->BackColor = Color::FromArgb(64, 64, 64); // Dark button background
						child->ForeColor = Color::White; // White text
					}
					else
					{
						child->BackColor = Color::FromArgb(240, 240, 240); // Light button background
						child->ForeColor = Color::Black; // Black text
					}
				}
				else
				{
					// Default theme colors for other controls
					if (CurrentTheme == ThemeType::Dark)
					{
						child->BackColor = Color::FromArgb(48, 48, 48); // Dark background
						child->ForeColor = Color::White; // White text
					}
					else
					{
						child->BackColor = Color::FromArgb(255, 255, 255); // Light background
						child->ForeColor = Color::Black; // Black text
					}
				}
				
				// Force immediate redraw
				child->Invalidate();
				child->Update();
			}
		}
		
		// Force update all controls with additional checks
		static void ForceUpdateAllControls(Form^ form)
		{
			if (form == nullptr) return;
			
			// Force update all controls recursively with additional theme enforcement
			ForceUpdateAllControlsRecursive(form);
			
			// Force the form to completely redraw
			form->Invalidate();
			form->Update();
			form->Refresh();
			
			// Additional force update for problematic tab pages
			ForceUpdateTabPages(form);
		}
		
		// Recursively force update all controls with additional theme enforcement
		static void ForceUpdateAllControlsRecursive(Control^ control)
		{
			if (control == nullptr) return;
			
			// Force update all control types regardless of their current state
			try
			{
				// Always force the control to use current theme colors
				control->BackColor = (CurrentTheme == ThemeType::Dark) ? DarkControlBackColor : LightControlBackColor;
				control->ForeColor = (CurrentTheme == ThemeType::Dark) ? DarkControlForeColor : LightControlForeColor;
				
				// Force immediate redraw
				control->Invalidate();
				control->Update();
			}
			catch (Exception^)
			{
				// Some controls don't support these properties, ignore errors
			}
			
			// Special handling for controls that might be in the Image section
			// These controls often have hardcoded colors that need to be overridden
			if (control->GetType() == Panel::typeid || 
				control->GetType() == GroupBox::typeid ||
				control->GetType() == TabPage::typeid ||
				control->GetType() == Label::typeid)
			{
				// Force these controls to use the exact theme colors
				if (CurrentTheme == ThemeType::Dark)
				{
					control->BackColor = Color::FromArgb(48, 48, 48); // Dark control background
					control->ForeColor = Color::White; // White text
				}
				else
				{
					control->BackColor = Color::FromArgb(255, 255, 255); // Light control background
					control->ForeColor = Color::Black; // Black text
				}
				
				// Force immediate redraw
				control->Invalidate();
				control->Update();
			}
			
			// Recursively process all child controls
			for each (Control^ child in control->Controls)
			{
				ForceUpdateAllControlsRecursive(child);
			}
		}
		
		// Force update tab pages specifically
		static void ForceUpdateTabPages(Form^ form)
		{
			if (form == nullptr) return;
			
			// Find all TabControl and TabPage controls
			ForceUpdateTabPagesRecursive(form);
		}
		
		// Recursively find and update tab pages
		static void ForceUpdateTabPagesRecursive(Control^ control)
		{
			if (control == nullptr) return;
			
			// Check if this is a TabControl
			if (control->GetType() == TabControl::typeid)
			{
				TabControl^ tabControl = dynamic_cast<TabControl^>(control);
				if (tabControl != nullptr)
				{
					// Force update the TabControl itself
					if (CurrentTheme == ThemeType::Dark)
					{
						tabControl->BackColor = Color::FromArgb(45, 45, 48); // Dark tab background
						tabControl->ForeColor = Color::White; // White text for tabs
					}
					else
					{
						tabControl->BackColor = SystemColors::Control;
						tabControl->ForeColor = SystemColors::ControlText;
					}
					
					// Force update all TabPages
					for each (TabPage^ tabPage in tabControl->TabPages)
					{
						if (tabPage != nullptr)
						{
							if (CurrentTheme == ThemeType::Dark)
							{
								tabPage->BackColor = Color::FromArgb(30, 30, 30); // Darker background for content
								tabPage->ForeColor = Color::White; // White text for content
							}
							else
							{
								tabPage->BackColor = SystemColors::Control;
								tabPage->ForeColor = SystemColors::ControlText;
							}
							
							// Force immediate redraw
							tabPage->Invalidate();
							tabPage->Update();
							
							// Force update all controls in this tab page
							ForceUpdateImageChildControls(tabPage);
						}
					}
					
					// Force immediate redraw
					tabControl->Invalidate();
					tabControl->Update();
				}
			}
			
			// Recursively process all child controls
			for each (Control^ child in control->Controls)
			{
				ForceUpdateTabPagesRecursive(child);
			}
		}

		// Toggle between light and dark themes
		static void ToggleTheme()
		{
			currentTheme = (currentTheme == ThemeType::Light) ? ThemeType::Dark : ThemeType::Light;
			SaveTheme();
			
			// Force immediate theme update
			Application::DoEvents();
			
			// Schedule a delayed update to catch any remaining controls
			ScheduleDelayedThemeUpdate();
		}
		
		// Schedule a delayed theme update to catch any remaining controls
		static void ScheduleDelayedThemeUpdate()
		{
			// Use a timer to delay the update and catch any controls that didn't update immediately
			System::Windows::Forms::Timer^ delayTimer = gcnew System::Windows::Forms::Timer();
			delayTimer->Interval = 100; // 100ms delay
			delayTimer->Tick += gcnew System::EventHandler(&CThemeManager::OnDelayedThemeUpdate);
			delayTimer->Start();
		}
		
		// Event handler for delayed theme update
		static void OnDelayedThemeUpdate(Object^ sender, EventArgs^ e)
		{
			System::Windows::Forms::Timer^ delayTimer = dynamic_cast<System::Windows::Forms::Timer^>(sender);
			if (delayTimer != nullptr)
			{
				// Force one more complete update after the delay
				delayTimer->Stop();
				delete delayTimer;
				
				// Force application to process any pending messages
				Application::DoEvents();
			}
		}

		// Apply theme to a control and all its children recursively
		static void ApplyThemeToControl(Control^ control)
		{
			if (control == nullptr) return;
			
			// Force the control to update its appearance
			control->SuspendLayout();
			
			// Apply theme based on control type
			if (control->GetType() == ComboBox::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == GroupBox::typeid)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (control->GetType() == Panel::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == Label::typeid)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (control->GetType() == Button::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == CheckBox::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == RadioButton::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == TextBox::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == ProgressBar::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == ListBox::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == ScrollBar::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == TreeView::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == TabControl::typeid)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
				
				// Apply theme to TabControl specifically for better tab appearance
				TabControl^ tabControl = dynamic_cast<TabControl^>(control);
				if (tabControl != nullptr)
				{
					// Set tab colors for better visibility in dark mode
					if (CurrentTheme == ThemeType::Dark)
					{
						tabControl->BackColor = Color::FromArgb(45, 45, 48); // Dark tab background
						tabControl->ForeColor = Color::White; // White text for tabs
					}
					else
					{
						tabControl->BackColor = SystemColors::Control;
						tabControl->ForeColor = SystemColors::ControlText;
					}
				}
			}
			else if (control->GetType() == TabPage::typeid)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
				
				// Apply theme to TabPage specifically
				TabPage^ tabPage = dynamic_cast<TabPage^>(control);
				if (tabPage != nullptr)
				{
					// Set tab page colors for better visibility
					if (CurrentTheme == ThemeType::Dark)
					{
						tabPage->BackColor = Color::FromArgb(30, 30, 30); // Darker background for content
						tabPage->ForeColor = Color::White; // White text for content
					}
					else
					{
						tabPage->BackColor = SystemColors::Control;
						tabPage->ForeColor = SystemColors::ControlText;
					}
				}
			}
			else if (control->GetType() == NumericUpDown::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == TrackBar::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == CheckedListBox::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == PictureBox::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == Splitter::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == RichTextBox::typeid)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (control->GetType() == MainMenu::typeid)
			{
				// MainMenu doesn't have BackColor/ForeColor properties
				// The theming will be handled by the system based on the parent form's theme
			}
			else if (control->GetType() == StatusBar::typeid)
			{
				control->BackColor = StatusBarBackColor;
				control->ForeColor = StatusBarForeColor;
			}
			else if (control->GetType() == ToolStrip::typeid)
			{
				control->BackColor = ToolStripBackColor;
				control->ForeColor = ToolStripForeColor;
				
				// Force the ToolStrip to use the new colors
				ToolStrip^ toolStrip = safe_cast<ToolStrip^>(control);
				if (toolStrip != nullptr)
				{
					toolStrip->Renderer = gcnew ToolStripProfessionalRenderer();
				}
			}
			else
			{
				// Apply default theme to any other control types
				try
				{
					control->BackColor = ControlBackColor;
					control->ForeColor = ControlForeColor;
				}
				catch (Exception^)
				{
					// Some controls don't support BackColor/ForeColor, ignore errors
				}
			}
			
			// Resume layout and force redraw
			control->ResumeLayout(false);
			control->Invalidate();
			
			// Apply theme to all child controls
			for each (Control^ child in control->Controls)
			{
				ApplyThemeToControl(child);
			}
		}

		// Save current theme to configuration file
		static void SaveTheme()
		{
			if (String::IsNullOrEmpty(configFile)) return;

			try
			{
				File::WriteAllText(configFile, currentTheme.ToString());
			}
			catch (Exception^)
			{
				// Silently fail if we can't save the theme
			}
		}

		// Load theme from configuration file
		static void LoadTheme()
		{
			if (String::IsNullOrEmpty(configFile)) return;

			try
			{
				if (File::Exists(configFile))
				{
					String^ themeText = File::ReadAllText(configFile);
					if (themeText == "Dark")
					{
						currentTheme = ThemeType::Dark;
					}
					else
					{
						currentTheme = ThemeType::Light;
					}
				}
			}
			catch (Exception^)
			{
				// Silently fail if we can't load the theme, default to Light
				currentTheme = ThemeType::Light;
			}
		}
		
		// Final theme update to catch any remaining controls
		static void FinalThemeUpdate(Form^ form)
		{
			if (form == nullptr) return;
			
			// Force one more complete update of all controls
			form->Invalidate();
			form->Update();
			form->Refresh();
			
			// Force all child controls to update
			FinalThemeUpdateRecursive(form);
			
			// Additional final update for Image section specifically
			FinalImageSectionUpdate(form);
		}
		
		// Recursively final theme update
		static void FinalThemeUpdateRecursive(Control^ control)
		{
			if (control == nullptr) return;
			
			// Force final update of all controls
			control->Invalidate();
			control->Update();
			
			// Recursively process all child controls
			for each (Control^ child in control->Controls)
			{
				FinalThemeUpdateRecursive(child);
			}
		}
		
		// Final update specifically for Image section
		static void FinalImageSectionUpdate(Form^ form)
		{
			if (form == nullptr) return;
			
			// Find and force update the Image section one more time
			FinalImageSectionUpdateRecursive(form);
		}
		
		// Recursively find and update Image section controls
		static void FinalImageSectionUpdateRecursive(Control^ control)
		{
			if (control == nullptr) return;
			
			// Check if this is the Image section or related controls
			if (!String::IsNullOrEmpty(control->Name))
			{
				String^ controlName = control->Name->ToLower();
				if (controlName->Contains("image") || controlName->Contains("flags") || 
					controlName->Contains("grp") || controlName->Contains("panel"))
				{
					// Force these controls to use exact theme colors
					if (CurrentTheme == ThemeType::Dark)
					{
						control->BackColor = Color::FromArgb(48, 48, 48); // Dark background
						control->ForeColor = Color::White; // White text
					}
					else
					{
						control->BackColor = Color::FromArgb(255, 255, 255); // Light background
						control->ForeColor = Color::Black; // Black text
					}
					
					// Force immediate redraw
					control->Invalidate();
					control->Update();
					control->Refresh();
					
					// Force update all child controls
					for each (Control^ child in control->Controls)
					{
						if (child != nullptr)
						{
							// Force child controls to use theme colors
							if (CurrentTheme == ThemeType::Dark)
							{
								child->BackColor = Color::FromArgb(48, 48, 48); // Dark background
								child->ForeColor = Color::White; // White text
							}
							else
							{
								child->BackColor = Color::FromArgb(255, 255, 255); // Light background
								child->ForeColor = Color::Black; // Black text
							}
							
							// Force immediate redraw
							child->Invalidate();
							child->Update();
						}
					}
				}
			}
			
			// Recursively process all child controls
			for each (Control^ child in control->Controls)
			{
				FinalImageSectionUpdateRecursive(child);
			}
		}
	};
} 