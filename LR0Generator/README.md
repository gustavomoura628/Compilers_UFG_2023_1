# LR(0) Automata Generator  
How to use:  
Write Grammar description in a text file with the format:  
```
1 S' -> S  
2 S -> ( L )  
3 S -> x  
4 L -> S  
5 L -> L , S  
```
```bash
./generator grammar.txt > automata.xml
```  
  
load automata.xml into draw.io  
Arrange -> Layout -> Custom  
```json
[
  {
    "layout": "mxHierarchicalLayout",
    "config": {
      "orientation": "west",
      "intraCellSpacing": 30,
      "interRankCellSpacing": 100,
      "interHierarchySpacing": 60,
      "parallelEdgeSpacing": 10
    }
  }
]
```
(You could change interRankCellSpacing or any other attribute to get a more tailored result)  
  
Done!  
![Automata Example(automata_example.png)
