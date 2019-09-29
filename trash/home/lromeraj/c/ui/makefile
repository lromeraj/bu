all: ctarget clean ui

ui: ctarget
	./ctarget -e ui -c -r

clean: ctarget
	./ctarget -e ui -cl


ctarget:
	if [ ! -e "c-target" ]; then git clone https://github.com/lromeraj/c-target; fi
	cd c-target && make ctarget && cp ctarget ../
