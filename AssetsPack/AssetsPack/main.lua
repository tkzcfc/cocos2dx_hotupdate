local function main()
	require("doit")
	doit()
end

__G__TRACKBACK__ = function(msg)
    local msg = debug.traceback(msg, 3)
    print(msg)
    return msg
end

xpcall(main, __G__TRACKBACK__)