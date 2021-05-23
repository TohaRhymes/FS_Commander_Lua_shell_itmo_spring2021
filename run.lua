lcounter = require("libspo_lab2_fs_for_lua")

function istable(t)
    return type(t) == "table"
end

o = lcounter:info()

function expandObjFull(o, p)
    r = {}
    for k, v in pairs(o) do
        if istable(v) then
            print(p .. "" .. k .. " = {")
            expandObjFull(v, p .. " ")
            print(p .. "}")
        else
            print(p .. "" .. k .. " = " .. v)
        end
    end
end

expandObjFull(o, "")