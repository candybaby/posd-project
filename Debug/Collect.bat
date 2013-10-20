SET PATH=c:\Program Files (x86)\Microsoft Visual Studio 10.0\Team Tools\Performance Tools\
vsinstr @CommandOption.txt
vsperfcmd -start:coverage -output:POSD_ERDiagram_UnitTesting.coverage
POSD_ERDiagram_UnitTesting.exe
vsperfcmd -shutdown
echo Complete!
pause