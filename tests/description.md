# Isomorphic Tests

## Graph 1


``` mermaid  

graph  
  
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;

classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;  
  
Start(( ))  

V0((0))  

V1((1))  

V2((2))  

V3((3))  
  
class V1,V2 terminated_node;  

class V0,V3 normal_node;  
  
Start --> V0  

V0 -- a --> V2

V0 -- b --> V1

V1 -- a --> V0

V1 -- b --> V2

V2 -- a --> V3

V2 -- b --> V0

V3 -- a --> V3

V3 -- b --> V1

```

## Graph 2

``` mermaid

graph  
  
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;  

classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;  
  
Start(( ))  

V0((0))  

V1((1))  

V2((2))  

V3((3))  

  
class V1,V2 terminated_node;  

class V0,V3 normal_node;  
  
Start --> V0  

V0 -- a --> V1

V0 -- b --> V2

V1 -- a --> V1

V1 -- b --> V1

V2 -- a --> V3

V2 -- b --> V0

V3 -- a --> V0

V3 -- b --> V1

```
## Graph 3
``` mermaid  

graph    
    
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;

classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;    
    
Start(( ))

V0((0))

V1((1))

V2((2))

V3((3))    
    
class V3,V2 terminated_node;  class V1,V0 normal_node;    
    
Start --> V1  

V1 -- a --> V2  

V1 -- b --> V3  

V3 -- a --> V1  

V3 -- b --> V2  

V2 -- a --> V0  

V2 -- b --> V1  

V0 -- a --> V0  

V0 -- b --> V3  
  
```

## Graph 4


``` mermaid  

graph  
  
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;

classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;  
  
Start(( ))  

V0((0))  

V1((1))  

V2((2))  

V3((3))  
  
class V0,V1,V2 terminated_node;  

class V3 normal_node;  
  
Start --> V0  

V0 -- a --> V2

V0 -- b --> V1

V1 -- a --> V0

V1 -- b --> V2

V2 -- a --> V3

V2 -- b --> V0

V3 -- a --> V3

V3 -- b --> V1

```

## Graph 5

``` mermaid

graph  
  
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;

classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;  
  
Start(( ))  

V0((0))  

V1((1))  

V2((2))  

class V1 terminated_node;  

class V0,V2 normal_node;  
  
Start --> V0  

V0 -- a --> V2

V0 -- b --> V1

V1 -- a --> V0

V1 -- b --> V2

V2 -- a --> V0

V2 -- b --> V0

```

## Graph 6

``` mermaid

graph  
  
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;

classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;  
  
Start(( ))  

V0((0))  

V1((1))  

V2((2))  

class V1 terminated_node;  

class V0 normal_node;  
  
Start --> V0  

V0 -- a --> V1

V1 -- a --> V1

```