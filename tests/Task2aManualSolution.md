
## Регулярное выражение
$$ a(a(ab)^*a(ab)^*+b)^*$$
## НКА
Построение НКА выполнено методом пристального взгляда.
``` mermaid  
graph LR 
  
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;  
classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;  
  
Start(( ))  
V0((0))  
V1((1))  
V2((2))  
V3((3))  
V4((4))  
V5((5))  
  
class V1 terminated_node;  
class V0,V2,V3,V4,V5 normal_node;  
  
Start --> V0
V0 -- a --> V1
V1 -- b --> V1
V1 -- a --> V2
V2 -- a --> V3
V3 -- b --> V2
V2 -- a --> V4
V4 -- a --> V5
V5 -- b --> V4
V4 -- eps --> V1
  
```
## НКА без $\varepsilon$-переходов
1) Построить транзитивное замыкание, графа только из $\varepsilon$-переходов. Добавить все эти переходы к исходному графу.
2) Если есть ребро v -- $\varepsilon$ --> u, где u - терминальное, то сделать v терминальной.
3) Если есть ребра v -- $\varepsilon$ --> u и u -- l --> w, то добавить ребро v -- l --> w.
4) Удалить все $\varepsilon$-ребра

``` mermaid  
graph LR 
  
classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;  
classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;  
  
Start(( ))  
V0((0))  
V1((1))  
V2((2))  
V3((3))  
V4((4))  
V5((5))  
  
class V1,V4 terminated_node;  
class V0,V2,V3,V5 normal_node;  
  
Start --> V0
V0 -- a --> V1
V1 -- b --> V1
V1 -- a --> V2
V2 -- a --> V3
V3 -- b --> V2
V2 -- a --> V4
V4 -- a --> V5
V5 -- b --> V4
V4 -- b --> V1
V4 -- a --> V2
  
```
## ПДКА
| Вершины | a    | b   | N   | Терминальная |
| ------- | ---- | --- | --- | ------------ |
| 0       | 1    | -   | 0   |              |
| 1       | 2    | 1   | 1   |              |
| -       | -    | -   | 2   | +            |
| 2       | 34   | -   | 3   |              |
| 34      | 25   | 12  | 4   | +            |
| 25      | 34   | 4   | 5   |              |
| 12      | 234  | 1   | 6   | +            |
| 4       | 25   | 1   | 7   | +            |
| 234     | 2345 | 12  | 8   | +            |
| 2345    | 2345 | 124 | 9   | +            |
| 124     | 2345 | 1   | 10  | +            |
``` mermaid

graph TB

classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;
classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;

Start(( ))
V0((0))
V1((1))
V2((2))
V3((3))
V4((4))
V5((5))
V6((6))
V7((7))
V8((8))
V9((9))
V10((10))

class V1,V4,V6,V7,V8,V9,V10, terminated_node;
class V0,V2,V3,V5, normal_node;

Start --> V0
V0 -- a ---> V1
V0 -- b ---> V2
V1 -- a ---> V3
V1 -- b ---> V1
V2 -- a ---> V2
V2 -- b ---> V2
V3 -- a ---> V4
V3 -- b ---> V2
V4 -- a ---> V5
V4 -- b ---> V6
V5 -- a ---> V4
V5 -- b ---> V7
V6 -- a ---> V8
V6 -- b ---> V1
V7 -- a ---> V5
V7 -- b ---> V1
V8 -- a ---> V9
V8 -- b ---> V6
V9 -- a ---> V9
V9 -- b ---> V10
V10 -- a ---> V9
V10 -- b ---> V1

```
## МПДКА
| N      | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  |
| ------ | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| ==~0== | 0   | 1   | 0   | 0   | 1   | 0   | 1   | 1   | 1   | 1   | 1   |
| a      | 1   | 0   | 0   | 1   | 0   | 1   | 1   | 0   | 1   | 1   | 1   |
| b      | 0   | 1   | 0   | 0   | 1   | 1   | 1   | 1   | 1   | 1   | 1   |
| ==~1== | 0   | 1   | 2   | 0   | 1   | 3   | 4   | 1   | 4   | 4   | 4   |
| a      | 1   | 0   | 2   | 1   | 3   | 1   | 4   | 3   | 4   | 4   | 4   |
| b      | 2   | 1   | 2   | 2   | 4   | 1   | 1   | 1   | 4   | 4   | 1   |
| ==~2== | 0   | 1   | 2   | 0   | 3   | 4   | 5   | 6   | 7   | 7   | 5   |
| a      | 1   | 0   | 2   | 3   | 4   | 3   | 7   | 4   | 7   | 7   | 7   |
| b      | 2   | 1   | 2   | 2   | 5   | 6   | 1   | 1   | 5   | 5   | 1   |
| ==~3== | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 8   | 6   |
| a      | 1   | 3   | 2   | 4   | 5   | 4   | 8   | 5   | 8   | 8   | 8   |
| b      | 2   | 1   | 2   | 2   | 6   | 7   | 1   | 1   | 6   | 6   | 1   |
| ==~4== | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 8   | 6   |

``` mermaid

graph TB

classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;
classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;

Start(( ))
V0((0))
V1((1))
V2((2))
V3((3))
V4((4))
V5((5))
V6((6))
V7((7))
V8((8))

class V1,V4,V6,V7,V8, terminated_node;
class V0,V2,V3,V5, normal_node;

Start --> V0
V0 -- a ---> V1
V0 -- b ---> V2
V1 -- a ---> V3
V1 -- b ---> V1
V2 -- a ---> V2
V2 -- b ---> V2
V3 -- a ---> V4
V3 -- b ---> V2
V4 -- a ---> V5
V4 -- b ---> V6
V5 -- a ---> V4
V5 -- b ---> V7
V6 -- a ---> V8
V6 -- b ---> V1
V7 -- a ---> V5
V7 -- b ---> V1
V8 -- a ---> V8
V8 -- b ---> V6

```
