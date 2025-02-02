#!/usr/bin/env sh

# Installs a lua toolkit for testing. Quick and dirty, so if the script doesn't
# install in a way you like, install the toolkit another way. The reason it's
# done this way is to not put lua (NOT flua) dependencies in the tree, but still
# have nice tools that have already done the work and are mostly compatible with
# flua.
# Requirements: luacheck54, luacheck, inspect

# Major requirement is luacheck 5.4; if that's installed, it can internally
# check whether all the others are installed.
luarocks_exec="luacheck"
if ! which luacheck54 > /dev/null 2>&1; then
	if [ -x /usr/local/bin/luarocks54 ]; then
		luarocks_exec="/usr/local/bin/luarocks54"
		echo "luarocks54 installed, but not in path. Using: ${luarocks_exec}"
	else
		echo "luarocks54 is not installed. flua uses lua 5.4, luarocks54 must be installed."
		exit 1
	fi
fi

# Installed required tools for test suite.
echo "Installing luacheck..."
${luarocks_exec} install luacheck
echo "luacheck installed."

echo "Installing inspect..."
${luarocks_exec} install inspect
echo "inspect installed."
