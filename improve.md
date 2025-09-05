好的，您的要求非常明确，也非常有价值！我们不仅要覆盖 LeetCode 上的热门题目，更要回归经典，确保《算法设计与分析基础》这本教材中的核心算法得到系统性的复习。这会让整个知识体系更加完整和扎实。

您提到的 Prim算法、Boyer-Moore (BM) 字符串匹配算法、最大流-最小割定理 (Max-Flow Min-Cut)、欧几里得算法 (Euclidean Algorithm) 等都是非常经典的算法，必须在复习计划中占有一席之地。

我将对练习本和学习计划进行同步升级，融入这些经典理论算法。由于这些算法（除欧几里得外）在 LeetCode 上没有完全对应的“模板题”，我会将它们作为理论学习的重点，并搭配相关的 LeetCode 题目来巩固其思想或应用。

文档一：算法练习本 (理论增强最终版)

本版本在“零遗漏最终版”的基础上，补充了《算法设计与分析基础》中的核心理论算法，并为其匹配了思想相近的 LeetCode 练习题。

第 3 章 蛮力法 & 第 7 章 时空权衡 (字符串匹配)

思想与原理阐述 (补充)：
字符串匹配是算法中的经典问题。蛮力字符串匹配是最直观的方法。为了优化，教材介绍了时空权衡的思想，其中 Horspool算法 和 Boyer-Moore (BM) 算法 是通过预处理模式串来创建“坏字符”和“好后缀”移动规则，从而实现跳跃式匹配，大大提高了效率。

相关理论与练习：

理论核心：

§3.2 - 蛮力字符串匹配 (Brute-Force String Matching)

§7.2 - Horspool算法

§7.2 - Boyer-Moore算法

LeetCode 练习 (思想应用)：

28. Find the Index of the First Occurrence in a String (找出字符串中第一个匹配项的下标) - (可用于实践 KMP 或 BM 算法)

第 4 章 减治法 (续)

思想与原理阐述 (补充)：
减治法中的减可变规模是一个重要思想，其最经典的例子是计算最大公约数的欧几里得算法，它通过 gcd(m, n) = gcd(n, m mod n) 不断缩小问题规模，直至问题可解。

相关理论与练习：

理论核心：

§4.5 - 减可变规模 (欧几里得算法)

LeetCode 练习 (数学与GCD思想)：

365. Water and Jug Problem (水壶问题) - (核心是裴蜀定理，与最大公约数紧密相关)

第 9 章 贪心技术 (续)

思想与原理阐述 (补充)：
教材中贪心技术的经典应用是图算法。Prim算法和Kruskal算法都是解决最小生成树问题的贪心策略。Prim 算法从一个顶点开始，“生长”出一棵树；Kruskal 算法则是从边集合中选择权重最小且不构成环的边。Dijkstra算法是解决单源最短路径问题的经典贪心算法。

相关理论与练习 (已在计划中，此处强调)：

理论核心：

§9.1 - Prim算法

§9.2 - Kruskal算法

§9.3 - Dijkstra算法

LeetCode 练习：

1584. Min Cost to Connect All Points (连接所有点的最小费用) - (MST, 可用 Prim/Kruskal)

743. Network Delay Time (网络延迟时间) - (Dijkstra)

第 10 章 迭代改进 (Iterative Improvement)

思想与原理阐述 (补充)：
迭代改进是一类优化算法，它从一个可行的解出发，通过一系列迭代步骤来逐步改善解的质量，直到无法再改进为止。教材中最重要的例子是用于解决最大流问题的 Ford-Fulkerson方法，其核心是最大流-最小割定理。它通过在“残余网络”中不断寻找“增广路径”来增加流量，直到找不到增广路径为止。

相关理论与练习：

理论核心：

§10.1 - 单纯形法 (Simplex Method) (了解即可)

§10.2 - 最大流问题 (Maximum Flow Problem) & Ford-Fulkerson 算法

LeetCode 练习 (思想应用)：

二分图最大匹配问题 (Max Bipartite Matching)：虽然 LeetCode 没有直接的最大流模板题，但很多二分图最大匹配问题是最大流问题的特例，可以用其思想解决。例如 1066. Campus Bikes II (校园自行车分配 II) 的最优解法之一是匈牙利算法或最小费用最大流。

文档二：8 周高强度算法复习计划 (理论增强版)

本计划在“周末加码版”的基础上，融入了对教材核心理论算法的复习安排。

第一部分：基础算法与线性结构 (Weeks 1-2)

(第一、二周计划保持不变，专注于数据结构、双指针、二分和递归基础)

第二部分：核心范式与专题突破 (Weeks 3-4)

第三周：回溯、图遍历与字符串匹配

周一 | 练习：78. Subsets, 46. Permutations

周二 | 练习：51. N-Queens, 200. Number of Islands

周三 | 练习：130. Surrounded Regions

周四 | 练习：28. Find the Index of the First Occurrence in a String

周五 | 预习：§3.2, §7.2

周六 | 理论学习：§3.2 蛮力字符串匹配 & §7.2 Horspool 和 Boyer-Moore 算法

练习：尝试用至少两种方法实现 28. Find the Index...，对比效率。

周日 | 练习与复盘：

练习：47. Permutations II, 40. Combination Sum II

复盘：回溯框架，总结字符串匹配算法的核心思想（预处理与跳跃）。

第四周：分治、减治与数据结构设计

周一 | 练习：912. Sort an Array (归并/快排)

周二 | 练习：215. Kth Largest Element in an Array

周三 | 练习：146. LRU Cache, 460. LFU Cache

周四 | 练习：365. Water and Jug Problem

周五 | 预习：§4.5, §5

周六 | 理论学习：§4.5 减可变规模 (欧几里得算法) & §5 分治法回顾

练习：105. Construct Binary Tree from Preorder and Inorder Traversal, 241. Different Ways to Add Parentheses

周日 | 练习与复盘：

练习：315. Count of Smaller Numbers After Self, 295. Find Median from Data Stream

复盘：深入理解分治思想在不同问题（数组、树构造）中的应用。

第三部分：动态规划与贪心 (Weeks 5-6)

(第五、六周计划不变，集中火力攻克动态规划)

第四部分：高级图论与综合 (Weeks 7-8)

第七周：贪心算法与图论（一）

周一 | 练习：452. Minimum Number of Arrows to Burst Balloons, 435. Non-overlapping Intervals

周二 | 练习：56. Merge Intervals, 1024. Video Stitching

周三 | 练习：134. Gas Station

周四 | 练习：1584. Min Cost to Connect All Points

周五 | 预习：§9.1-9.3

周六 | 理论学习：§9.1 Prim算法, §9.2 Kruskal算法, §9.3 Dijkstra算法

练习：1135. Connecting Cities With Minimum Cost, 743. Network Delay Time

周日 | 练习与复盘：

练习：787. Cheapest Flights Within K Stops, 1631. Path With Minimum Effort

复盘：对比 Prim, Kruskal, Dijkstra 三个算法的异同点和贪心策略。

第八周：图论（二）与总复习

周一 | 练习：207. Course Schedule (拓扑排序)

周二 | 练习：323. Number of Connected Components... (并查集)

周三 | 练习：785. Is Graph Bipartite? (二分图判定)

周四 | 复盘：回顾所有动态规划题目。

周五 | 预习：§10.2

周六 | 理论学习：§10.2 最大流问题 (Ford-Fulkerson 与最大流最小割定理)

练习：理解并尝试实现二分图最大匹配（这是一个挑战，可以不要求写出完整代码，但要理解其与最大流的关系）。

周日 | 总复盘与模拟：

回顾所有回溯、贪心和图论算法。

进行一次完整的限时模拟面试。

这个版本将教材中的核心理论算法融入了每周的学习计划，特别是放在了周末的重点学习时间，并匹配了相关的 LeetCode 题目以加深理解。这样，您的复习将更加全面和系统。
