# LR(0) Automata Generator  
How to use:  
Write Grammar description in the format (1) A -> B + C  
```bash
./generator grammar.txt > automata.xml
```  
load xml file into draw.io  
Arrange -> Layout -> Custom  
```json
[
  {
    "layout": "mxHierarchicalLayout",
    "config": {
      "orientation": "west",
      "intraCellSpacing": 30,
      "interRankCellSpacing": 300,
      "interHierarchySpacing": 60,
      "parallelEdgeSpacing": 10
    }
  }
]
```
Done!  
