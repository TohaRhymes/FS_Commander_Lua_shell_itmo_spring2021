---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by toharhymes.
--- DateTime: 25.05.2021 0:23
---

printf = function(s, ...)
    return io.write(s:format(...))
end

function print_help()
    print("\t* To run program in list mode use `list` key.")
    print("\t* To run it in shell mode use `commander` key and specify drive or deviceDescriptor.\n")

end

function print_info(o, p)
    print("System partition:\nname\t\tsize\ttype")
    for k, v in pairs(o) do
        print(v["name"] .. "\t" .. v["size"] .. " " .. v["metric"] .. "\t" .. v["type"])
    end
end

function shell(name)
    --CHECK DETECTION
    print("NTFS filesystem detected.")
    pwd_path = "kek"
    exit_flag = false
    while not exit_flag do
        printf("%s$ ", pwd_path)
        input_string = io.read()
        if input_string == "" then
            goto continue
        elseif input_string == "exit" then
            exit_flag = true
            print("Terminating...")
        elseif input_string == "help" then
            print("--------------------------------------------------------")
            print("COMMAND\t\t| DESCRIPTION")
            print("----------------| --------------------------------------")
            print("cd [directory]\t| change working directory")
            print("pwd\t\t| print full path to working directory")
            print("cp [from] [to]\t| copy dir or file from mounted device")
            print("ls/ll\t\t| show working directory elements")
            print("exit\t\t| terminate program")
            print("help\t\t| print help")
            print("--------------------------------------------------------")
        else
            print("Wrong command. Enter 'help' to get help.")
        end
        :: continue ::
    end
end

genius_lib = require("libspo_lab2_fs_for_lua")
if arg[1] == "help" then
    print_help()
    return 0
end
if arg[1] == "list" then
    o = genius_lib:info()
    print_info(o, "")
    return 0
end
if arg[1] == "commander" and arg[2] ~= nil then
    shell(arg[2])
    return 0
end
print("Incorrect command line arguments.");
print_help()
return 0


--function istable(t)
--    return type(t) == "table"
--end
--function expandObjFull(o, p)
--    for k, v in pairs(o) do
--        if istable(v) then
--            print(p .. "" .. k .. " = {")
--            expandObjFull(v, p .. " ")
--            print(p .. "}")
--        else
--            print(p .. "" .. k .. " = " .. v)
--        end
--    end
--end
