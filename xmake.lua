-- luacheck: ignore 111 113
---@diagnostic disable: undefined-global
add_rules("mode.debug", "mode.release")
add_requires("rime", "readline", "glib")

target("rl_custom_rime")
do
    set_kind("shared")
    add_files("*.c")
    add_includedirs("tmux-rime")
    add_undefines("_XOPEN_SOURCE")
    add_packages("rime", "readline", "glib")
    on_load(
        function(target)
            ---@diagnostic disable: undefined-field
            -- luacheck: ignore 143
            if not os.isdir("tmux-rime") then
                import("devel.git")
                git.clone("https://github.com/Freed-Wu/tmux-rime", { depth = 1 })
            end
            target:add("files", "tmux-rime/tmux-rime.c")
        end
    )
end
