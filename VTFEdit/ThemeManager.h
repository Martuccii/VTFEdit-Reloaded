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

		// Toggle between light and dark themes
		static void ToggleTheme()
		{
			currentTheme = (currentTheme == ThemeType::Light) ? ThemeType::Dark : ThemeType::Light;
			SaveTheme();
		}

		// Apply theme to a control and all its children recursively
		static void ApplyThemeToControl(Control^ control)
		{
			if (control == nullptr) return;
			
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
	};
} 