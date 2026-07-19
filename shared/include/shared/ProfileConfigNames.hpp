#pragma once

namespace ProfileConfig {

    namespace Key {

        namespace Profile {
            inline constexpr auto Key = "profiles";
            inline constexpr auto Uuid = "uuid";
            inline constexpr auto Name = "name";
            inline constexpr auto Shortcut = "shortcut";

            namespace View {
                inline constexpr auto Key = "view";
                inline constexpr auto Mode = "mode";
                inline constexpr auto HorizontalAnchor = "horizontal_anchor";
                inline constexpr auto VerticalAnchor = "vertical_anchor";
                inline constexpr auto Margin = "margin";
                inline constexpr auto WrapMode = "wrap_mode";
                inline constexpr auto FlowDirection = "flow_direction";
            } // namespace View

            namespace ExecutionTarget {
                inline constexpr auto Key = "execution_targets";
                inline constexpr auto Type = "type";
                inline constexpr auto Name = "name";
                inline constexpr auto IconFile = "icon_file";

                inline constexpr auto DesktopFile = "desktop_file";
                inline constexpr auto FileToOpen = "file_to_open";
                inline constexpr auto Url = "url";
                inline constexpr auto Command = "command";
                inline constexpr auto ExecutableFile = "executable_file";
                inline constexpr auto Arguments = "arguments";
                inline constexpr auto ExecutionTargets = "execution_targets";
            } // namespace ExecutionTarget

        } // namespace Profile

    }; // namespace Key

    namespace Value {

        namespace Profile {

            namespace View {

                namespace Mode {
                    inline constexpr auto Icon = "icon";
                    inline constexpr auto List = "list";
                }; // namespace Mode

                namespace HorizontalAnchor {
                    inline constexpr auto Left = "left";
                    inline constexpr auto Center = "center";
                    inline constexpr auto Right = "right";
                }; // namespace HorizontalAnchor

                namespace VerticalAnchor {
                    inline constexpr auto Top = "top";
                    inline constexpr auto Center = "center";
                    inline constexpr auto Bottom = "bottom";
                }; // namespace VerticalAnchor

                namespace FlowDirection {
                    inline constexpr auto Horizontal = "horizontal";
                    inline constexpr auto Vertical = "vertical";
                }; // namespace FlowDirection

                namespace WrapMode {
                    inline constexpr auto Scroll = "scroll";
                    inline constexpr auto Grid = "grid";
                }; // namespace WrapMode

            } // namespace View

            namespace ExecutionTarget {

                namespace Type {

                    inline constexpr auto DesktopApplication = "Desktop-Application";
                    inline constexpr auto ExecutableFile = "Executable-File";
                    inline constexpr auto Command = "Command";
                    inline constexpr auto OpenFile = "Open-File";
                    inline constexpr auto OpenUrl = "Open-Url";
                    inline constexpr auto Group = "Group";
                } // namespace Type

            } // namespace ExecutionTarget

        } // namespace Profile

    } // namespace Value

} // namespace ProfileConfig