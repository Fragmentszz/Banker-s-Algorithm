function generateDiv(totalDivs) {
    var divCount = 0;
    for (let i = 0;i<=totalDivs;i++) {
        var div = document.createElement('div');
        div.id = 'div_' + (i);
        div.style.width = '100%';
        div.style.height = '200px';
        document.body.appendChild(div);
        divCount++;
    }
}
function clearDivs() {
    const divs = document.querySelectorAll('div');
    divs.forEach(div => {
        if (div.id.startsWith('div_')) {
            div.remove();
        }
    });
}
var option0 = {
    graphic: {
      elements: [
        {
          type: 'text',
          left: '40%',
          top: '50%',
          style: {
            text: '',
            fontSize: 30,
            fontWeight: 'bold',
            lineDash: [0, 200],
            lineDashOffset: 0,
            //fill: 'transparent',
            stroke: '#000',
            lineWidth: 1
          },
          keyframeAnimation: {
            duration: 3000,
            loop: true,
            keyframes: [
              {
                percent: 0.5,
                easing: 'sinusoidalInOut',
                scaleX: 0.5,
                scaleY: 0.5
                }, {
                    percent: 1,
                    easing: 'sinusoidalInOut',
                    scaleX: 1,
                    scaleY: 1
                }
            ]
          }
        }
      ]
    }
  };
var linestyle = {
    opacity: 0.9,
    width: 2,
    curveness: 0
};

function runBA(flag,datas,scores)
{
    clearDivs();
    const n = datas.length;
    generateDiv(n);
    if(flag === 1){
        option0.graphic.elements[0].style.text = '不响应请求!\n请求资源超过该进程的\n总请求资源数！';
    }else if(flag === 2){
        option0.graphic.elements[0].style.text = '不响应请求!\n该进程当前的请求超过现有资源!';
    }else if(flag === 3){
        option0.graphic.elements[0].style.text = '不响应请求!\n响应请求后进入死锁状态！';
    }else{
        option0.graphic.elements[0].style.text = '可以响应请求!\n给出按照平均等待时长排序的可用分配路径:';
    }
    const div0 = document.getElementById('div_0');
    
    const width = div0.offsetWidth;
    const height = div0.offsetHeight;
    
    var myChart = echarts.init(div0);
    myChart.setOption(option0);
    if(flag !== 4)
    {
        // 将其设置为绝对定位
        div0.style.position = 'absolute';
        // 计算居中的top和left值
        const windowHeight = window.innerHeight;
        const windowWidth = window.innerWidth;
        const divHeight = div0.offsetHeight;
        const divWidth = div0.offsetWidth;
        const topValue = (windowHeight - divHeight) / 2;
        const leftValue = (windowWidth - divWidth) / 2;

        // 设置top和left值使其居中
        div0.style.top = topValue + 'px';
        div0.style.left = leftValue + 'px';
        return;
    }
    const m = datas[0].length;
    
    //console.log(width,height);
    var links = [];
    for(let i=0;i<m;i++)
    {
        links.push({
            source:i,
            target:i+1
        });
    }
    
    const lb = 25;
    const evx = (width-lb) / (m-1);
    for(let i=0;i<n;i++)
    {
        var data = [];
        for(let j=0;j<m;j++)
        {
            data.push({
               name:'进程' + datas[i][j],
               x: evx*j+lb,
               y:height / 2
            });
        }
        var option = {
            title: {
              text: '第' + (i+1) + '条路径---平均等待时长:' + scores[i]
            },
            tooltip: {},
            animationDurationUpdate: 1500,
            animationEasingUpdate: 'quinticInOut',
            series : 
            {
                type: 'graph',
                layout: 'none',
                symbolSize: 50,
                roam: true,
                label: {
                show: true
                },
                edgeSymbol: ['circle', 'arrow'],
                edgeLabel: {
                fontSize: 0,
                }, 
                data:data,
                links:links,
                lineStyle:linestyle
            }
        }
        let nowdiv = document.getElementById('div_' + (i + 1));
        var myChart = echarts.init(nowdiv);
        myChart.setOption(option);
    }
}