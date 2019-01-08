
output: ass_2main
	./ass_2main -i "file1.txt" > file1output.txt
	cat file1output.txt
	./ass_2main -i "file2.txt" > file2output.txt
	cat file2output.txt
	./ass_2main -i "file3.txt" > file3output.txt
	cat file3output.txt
	./ass_2main -i "file4.txt" > file4output.txt
	cat file4output.txt

assignment_1main.o: ass_2main.cpp 
	g++ -o ass_2main ass_2main.cpp	
clean:
	rm ass_2main
	rm file1output.txt
	rm file2output.txt
	rm file3output.txt
	rm file4output.txt


#  g++ -o myspeller assignment_1header.cpp assignment_1main.cpp 
# ./myspeller -d Dictionary141words.txt -l 4


#Branden_project_2 BrandenKang$ g++ ass_2main.cpp && ./a.out -i file2.txt
