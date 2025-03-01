target extended-remote localhost:1234
monitor reset halt
define bup
tui disable
monitor halt
shell auto-ocd -b
if $_shell_exitcode == 0
monitor reset halt
monitor flash write_image erase unlock ./build/CubeMX.elf 0 elf
monitor flash verify_image ./build/CubeMX.elf 0 elf
monitor reset halt
tui enable
run
tui refresh
end
end
define bnu
shell auto-ocd -b
end
define bupd
tui disable
monitor halt
shell rm -r ./build
shell auto-ocd -b
if $_shell_exitcode == 0
monitor reset halt
monitor flash write_image erase unlock ./build/CubeMX.elf 0 elf
monitor flash verify_image ./build/CubeMX.elf 0 elf
monitor reset halt
tui enable
run
tui refresh
end
end
tui enable
delete
b Calculator
run
