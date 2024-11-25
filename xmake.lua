-- luacheck: ignore 111 113
---@diagnostic disable: undefined-global
add_rules("mode.debug", "mode.release")
add_requires("rime")
add_requires("readline")
add_requires("glib")

includes("@builtin/check")
add_configfiles("tmux-rime/config.h.in")
configvar_check_cincludes("RIME_API_DEPRECATED", "rime_api_deprecated.h")

target("rl_custom_rime")
do
    set_kind("shared")
    add_includedirs("$(buildir)")
    add_files("tmux-rime/tmux-rime.c", "*.c")
    add_includedirs("tmux-rime")
    add_undefines("_XOPEN_SOURCE")
    add_packages("rime")
    add_packages("readline")
    add_packages("glib")
    before_build(
        function(target)
            ---@diagnostic disable: undefined-field
            -- luacheck: ignore 143
            if not os.isdir("tmux-rime") then
                import("devel.git")
                git.clone("https://github.com/Freed-Wu/tmux-rime", { depth = 1 })
            end
        end
    )
end