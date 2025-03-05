target extended-remote localhost:1234
monitor reset halt
define bup
tui disable
monitor halt
shell auto-ocd -b
if $_shell_exitcode == 0
monitor reset halt
monitor flash write_image erase unlock ./build/boot.elf 0 elf
monitor flash verify_image ./build/boot.elf 0 elf
monitor reset halt
tui enable
run
tui refresh
end
end
define bnu
shell auto-ocd -b
end
define pvec
    if $argc == 2
        set $elem = $arg0.size()
        if $arg1 >= $arg0.size()
            printf "Error, %s.size() = %d, printing last element:\n", "$arg0", $arg0.size()
            set $elem = $arg1 -1
        end
        print *($arg0._M_impl._M_start + $elem)@1
    else
        print *($arg0._M_impl._M_start)@$arg0.size()
    end
end
define bupd
tui disable
monitor halt
shell rm -r ./build
shell auto-ocd -b
if $_shell_exitcode == 0
monitor reset halt
monitor flash write_image erase unlock ./build/boot.elf 0 elf
monitor flash verify_image ./build/boot.elf 0 elf
monitor reset halt
tui enable
run
tui refresh
end
end
tui enable
delete
b boot
run
