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

		static property ThemeType CurrentTheme 
		{ 
			ThemeType get() { return currentTheme; }
			void set(ThemeType theme) 
			{ 
				currentTheme = theme; 
				SaveTheme();
			}
		}

		// Initialize theme manager
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
		}

		// Apply theme to a specific control and its children
		static void ApplyThemeToControl(Control^ control)
		{
			if (control == nullptr) return;

			// Apply theme based on control type
			if (dynamic_cast<Panel^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<GroupBox^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<TextBox^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<RichTextBox^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<ComboBox^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<CheckBox^>(control) != nullptr)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (dynamic_cast<RadioButton^>(control) != nullptr)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (dynamic_cast<Label^>(control) != nullptr)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (dynamic_cast<Button^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<TrackBar^>(control) != nullptr)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (dynamic_cast<NumericUpDown^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<TreeView^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
				control->ForeColor = ControlForeColor;
			}
			else if (dynamic_cast<TabControl^>(control) != nullptr)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (dynamic_cast<TabPage^>(control) != nullptr)
			{
				control->BackColor = BackColor;
				control->ForeColor = ForeColor;
			}
			else if (dynamic_cast<ProgressBar^>(control) != nullptr)
			{
				control->BackColor = ControlBackColor;
			}
			else if (dynamic_cast<MenuStrip^>(control) != nullptr)
			{
				control->BackColor = MenuBackColor;
				control->ForeColor = MenuForeColor;
			}
			else if (dynamic_cast<ToolStrip^>(control) != nullptr)
			{
				control->BackColor = ToolStripBackColor;
				control->ForeColor = ToolStripForeColor;
			}
			else if (dynamic_cast<StatusStrip^>(control) != nullptr)
			{
				control->BackColor = StatusBarBackColor;
				control->ForeColor = StatusBarForeColor;
			}

			// Apply to all child controls
			for each (Control^ child in control->Controls)
			{
				ApplyThemeToControl(child);
			}
		}

		// Toggle between light and dark themes
		static void ToggleTheme()
		{
			CurrentTheme = (CurrentTheme == ThemeType::Light) ? ThemeType::Dark : ThemeType::Light;
		}

	private:
		// Load theme from configuration
		static void LoadTheme()
		{
			if (String::IsNullOrEmpty(configFile)) return;

			try
			{
				if (IO::File::Exists(configFile))
				{
					array<String^>^ lines = IO::File::ReadAllLines(configFile);
					for each (String^ line in lines)
					{
						if (line->StartsWith("VTFEdit.Theme="))
						{
							String^ themeValue = line->Substring(13);
							if (themeValue == "Dark")
								currentTheme = ThemeType::Dark;
							else
								currentTheme = ThemeType::Light;
							break;
						}
					}
				}
			}
			catch (Exception^)
			{
				// If there's an error, default to light theme
				currentTheme = ThemeType::Light;
			}
		}

		// Save theme to configuration
		static void SaveTheme()
		{
			if (String::IsNullOrEmpty(configFile)) return;

			try
			{
				// Read existing config file
				if (IO::File::Exists(configFile))
				{
					array<String^>^ lines = IO::File::ReadAllLines(configFile);
					bool themeFound = false;
					
					// Look for existing theme line and update it
					for (int i = 0; i < lines->Length; i++)
					{
						if (lines[i]->StartsWith("VTFEdit.Theme="))
						{
							lines[i] = "VTFEdit.Theme=" + ((currentTheme == ThemeType::Dark) ? "Dark" : "Light");
							themeFound = true;
							break;
						}
					}
					
					// If theme line not found, add it after [VTFEdit] section
					if (!themeFound)
					{
						array<String^>^ newLines = gcnew array<String^>(lines->Length + 1);
						int insertIndex = 0;
						
						for (int i = 0; i < lines->Length; i++)
						{
							newLines[i] = lines[i];
							if (lines[i] == "[VTFEdit]")
							{
								insertIndex = i + 2; // Insert after [VTFEdit] and empty line
								break;
							}
						}
						
						// Shift lines to make room for theme line
						for (int i = lines->Length; i > insertIndex; i--)
						{
							newLines[i] = newLines[i - 1];
						}
						
						newLines[insertIndex] = "VTFEdit.Theme=" + ((currentTheme == ThemeType::Dark) ? "Dark" : "Light");
						lines = newLines;
					}
					
					IO::File::WriteAllLines(configFile, lines);
				}
			}
			catch (Exception^)
			{
				// Silently fail if we can't save the theme
			}
		}
	};
} 