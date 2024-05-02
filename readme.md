<!doctype html>
<html>
<head>
<meta charset='UTF-8'><meta name='viewport' content='width=device-width initial-scale=1'>
<h1 id='银行家算法计算器'><span>银行家算法计算器</span></h1>

> 写在前面: 这是AHU-大三下系统软件综合训练实验一，具体题目是为银行家算法开发一款有用户界面的软件
>
> 环境: ```QT6```+```JavaScript```

<div id='write'  class=''><h2 id='使用步骤'><span>使用步骤</span></h2><h3 id='1-创建项目从excel导入项目确定资源数和进程数最大资源需求量'><span>1. 创建项目/从excel导入项目：确定资源数和进程数，最大资源需求量</span></h3><p><span>首先通过创建项目确定系统中的资源个数和进程个数。 </span></p><p><img src=".\html\image-20240324221722581.png" referrerpolicy="no-referrer" alt="image-20240324221722581"></p><p><img src=".\html\image-20240324221952974.png" referrerpolicy="no-referrer" alt="image-20240324221952974"></p><p><span>确定好资源数量和进程数量以后，通过</span><strong><span>逐个输入</span></strong><span>或者是</span><strong><span>随机生成</span></strong><span>的方式，确定好每个进程的每种资源的最大需求量。</span></p><p><img src=".\html\image-20240324222208850.png" referrerpolicy="no-referrer" alt="image-20240324222208850"></p><p><span>当然，您也可以通过从</span><strong><span>excel</span></strong><span>中导入的方式来创建项目，并且从</span><strong><span>excel</span></strong><span>文件中获取每个进程每种资源的最大需求量。</span></p><p><img src=".\html\image-20240324222253126.png" referrerpolicy="no-referrer" alt="image-20240324222253126"></p><p>&nbsp;</p><h3 id='2-确定系统中的资源所有量'><span>2. 确定系统中的资源所有量</span></h3><p><img src=".\html\image-20240324222424151.png" referrerpolicy="no-referrer" alt="image-20240324222424151"></p><p><span>您可以逐个输入，当然也可以随机生成一组资源所有量：</span></p><p><img src=".\html\image-20240324222523209.png" referrerpolicy="no-referrer" alt="image-20240324222523209"></p><h2 id='3-确定各个进程的剩余服务时间以排序安全序列'><span>3. 确定各个进程的剩余服务时间以排序安全序列</span></h2><p><span>为了给所有安全序列一个排序，需要知晓每个进程的剩余服务时间。</span></p><p><span>当然，您可以逐个输入，也可以随机生成一组剩余服务时间。</span></p><p><img src=".\html\image-20240324222658585.png" referrerpolicy="no-referrer" alt="image-20240324222658585"></p><p><img src=".\html\image-20240324222732351.png" referrerpolicy="no-referrer" alt="image-20240324222732351"></p><h2 id='4-切换到allocation页面'><span>4. 切换到Allocation页面</span></h2><p><span>此时系统的预设部分已经完成，接下来完成分配和请求部分的设置。点击</span><code>Allocation</code><span>切换到分配标签页。</span></p><p><img src=".\html\image-20240324222937171.png" referrerpolicy="no-referrer" alt="image-20240324222937171"></p><h2 id='5-确定分配矩阵'><span>5. 确定分配矩阵</span></h2><p><span>对于每一进程的每一进程的分配您都可以手动输入，当然随机生成也是可以的。</span></p><p><img src=".\html\image-20240324223123503.png" referrerpolicy="no-referrer" alt="image-20240324223123503"></p><p><img src=".\html\image-20240324223218258.png" referrerpolicy="no-referrer" alt="image-20240324223218258"></p><blockquote><p><span>注意：现有资源列是根据系统最大资源和已分配资源自动计算的，不允许输入！</span></p></blockquote><p><img src=".\html\image-20240324223416726.png" referrerpolicy="no-referrer" alt="image-20240324223416726"></p><h2 id='6-确定请求进程号和请求向量'><span>6. 确定请求进程号和请求向量</span></h2><p><span>对于要请求资源的进程号必须手动输入：</span></p><p><img src=".\html\image-20240324223456850.png" referrerpolicy="no-referrer" alt="image-20240324223456850"></p><p><span>而对于请求向量则可以手动输入，也可以随机生成:</span></p><p><img src=".\html\image-20240324223547992.png" referrerpolicy="no-referrer" alt="image-20240324223547992"></p><p><img src=".\html\image-20240324223619048.png" referrerpolicy="no-referrer" alt="image-20240324223619048"></p><h2 id='7-运行银行家算法'><span>7. 运行银行家算法</span></h2><p><span>当以上步骤都完成，把所有表格都填完整以后，就可以运行银行家算法:</span></p><p><img src=".\html\image-20240324223738806.png" referrerpolicy="no-referrer" alt="image-20240324223738806"></p><p><span>根据执行结果即可判断是否响应该请求。</span></p><p><span>如何可以响应则会给出至多20条可行的路径，并且</span><strong><span>根据平均等待时间</span></strong><span>排序。</span></p><h2 id='8-更多'><span>8. 更多...</span></h2><p><span>当然，还有些剩余选项可以被挖掘，不过它们都非常简单，和字面描述的完全一致，因此交给您自己探索！</span></p></div></div>

