@echo off
echo delete build files...

del /s *.suo
del /s *.ilk
del /s *.pdb
del /s *.log
del /s *.obj
del /s *.idb
del /s *.pdb
del /s *.tlog
del /s *.lastbuildstate
del /s *.VC.db

echo ok!
exit