let network = null;
let nodesDataSet = new vis.DataSet();
let edgesDataSet = new vis.DataSet();

const COLOR_DEFAULT = '#3b82f6';
const COLOR_HIGHLIGHT = '#f59e0b';
const COLOR_CRITICAL = '#ef4444';
const COLOR_EDGE_OPEN = 'rgba(148, 163, 184, 0.4)';
const COLOR_EDGE_CLOSED = 'rgba(239, 68, 68, 0.2)';
const COLOR_EDGE_HIGHLIGHT = '#f59e0b';

// 初始化图表
function initGraph() {
    const container = document.getElementById('network-canvas');
    const data = {
        nodes: nodesDataSet,
        edges: edgesDataSet
    };
    
    const options = {
        nodes: {
            shape: 'dot',
            size: 15,
            font: { color: '#f8fafc', size: 12, face: 'Inter' },
            borderWidth: 2,
            color: {
                background: '#1e293b',
                border: COLOR_DEFAULT,
                highlight: { background: '#334155', border: '#60a5fa' }
            },
            shadow: { enabled: true, color: 'rgba(59, 130, 246, 0.5)', size: 10 }
        },
        edges: {
            width: 2,
            color: COLOR_EDGE_OPEN,
            smooth: { type: 'continuous' }
        },
        physics: {
            forceAtlas2Based: { gravitationalConstant: -50, centralGravity: 0.005, springLength: 100, springConstant: 0.18 },
            maxVelocity: 50,
            solver: 'forceAtlas2Based',
            timestep: 0.35,
            stabilization: { iterations: 150 }
        },
        interaction: {
            hover: true,
            tooltipDelay: 200,
            zoomView: true
        }
    };

    network = new vis.Network(container, data, options);

    network.on("click", function (params) {
        if (params.nodes.length > 0) {
            const nodeId = params.nodes[0];
            const nodeData = nodesDataSet.get(nodeId);
            showNodeInfo(nodeData);
        } else {
            document.getElementById('node-info').innerHTML = "点击左侧图表中的地点查看详情...";
        }
    });
}

function showNodeInfo(data) {
    const html = `
        <div class="info-row"><span class="info-label">编号</span> <span>${data.id}</span></div>
        <div class="info-row"><span class="info-label">名称</span> <span style="color:#e2e8f0; font-weight:600">${data.label}</span></div>
        <div class="info-row"><span class="info-label">类型</span> <span>${data.category || 'N/A'}</span></div>
        <div class="info-row"><span class="info-label">开放时间</span> <span>${data.open_time} - ${data.close_time}</span></div>
        <div class="info-row"><span class="info-label">停留耗时</span> <span>${data.stay_time} 分钟</span></div>
    `;
    document.getElementById('node-info').innerHTML = html;
}

// 读取并解析 CSV
async function loadData() {
    try {
        // 读取 Places
        const placesRes = await fetch('../data/places.csv');
        const placesText = await placesRes.text();
        Papa.parse(placesText, {
            header: true,
            skipEmptyLines: true,
            complete: function(results) {
                const nodes = results.data.map(row => ({
                    id: row.id,
                    label: row.name,
                    category: row.category,
                    stay_time: row.stay_time,
                    open_time: row.open_time,
                    close_time: row.close_time
                }));
                nodesDataSet.add(nodes);
            }
        });

        // 读取 Roads
        const roadsRes = await fetch('../data/roads.csv');
        const roadsText = await roadsRes.text();
        Papa.parse(roadsText, {
            header: true,
            skipEmptyLines: true,
            complete: function(results) {
                const edges = results.data.map(row => {
                    const isClosed = row.status === 'closed';
                    return {
                        id: row.id,
                        from: row.from_id,
                        to: row.to_id,
                        label: row.walk_time + 'm',
                        font: { align: 'top', color: '#64748b', size: 10 },
                        color: isClosed ? COLOR_EDGE_CLOSED : COLOR_EDGE_OPEN,
                        dashes: isClosed
                    };
                });
                edgesDataSet.add(edges);
            }
        });

        initGraph();
    } catch (e) {
        console.error("加载数据失败，请确保使用本地服务器运行 (如 python -m http.server)", e);
        document.getElementById('node-info').innerHTML = `<span style="color:#ef4444">加载本地 CSV 失败。<br>请在命令行运行 <code>python -m http.server</code>，然后通过 localhost:8000 访问本页面。</span>`;
    }
}

// 演示最短路径高亮
function highlightDemoPath() {
    resetGraph();
    // 假设这是 C++ 程序跑出来的 P0001 到 P0050 的一条最短路
    const demoPathNodes = ["P0001", "P0002", "P0006", "P0016", "P0050"];
    
    // 高亮节点
    const updatedNodes = demoPathNodes.map(id => {
        const node = nodesDataSet.get(id);
        if(node) {
            return {
                id: id,
                color: { border: COLOR_HIGHLIGHT, background: '#1e293b' },
                shadow: { color: COLOR_HIGHLIGHT, size: 15 },
                borderWidth: 3
            };
        }
        return null;
    }).filter(n => n !== null);
    nodesDataSet.update(updatedNodes);

    // 寻找并高亮路径上的边
    const updatedEdges = [];
    const allEdges = edgesDataSet.get();
    
    for (let i = 0; i < demoPathNodes.length - 1; i++) {
        const u = demoPathNodes[i];
        const v = demoPathNodes[i+1];
        
        const edge = allEdges.find(e => (e.from === u && e.to === v) || (e.from === v && e.to === u));
        if (edge) {
            updatedEdges.push({
                id: edge.id,
                color: COLOR_EDGE_HIGHLIGHT,
                width: 4
            });
        }
    }
    edgesDataSet.update(updatedEdges);
    
    // 聚焦摄像机
    network.fit({
        nodes: demoPathNodes,
        animation: { duration: 1000, easingFunction: 'easeInOutQuad' }
    });
}

function resetGraph() {
    // 恢复所有节点颜色
    const updatedNodes = nodesDataSet.get().map(node => ({
        id: node.id,
        color: { border: COLOR_DEFAULT, background: '#1e293b' },
        shadow: { color: 'rgba(59, 130, 246, 0.5)', size: 10 },
        borderWidth: 2
    }));
    nodesDataSet.update(updatedNodes);

    // 恢复所有边颜色
    const updatedEdges = edgesDataSet.get().map(edge => {
        const isClosed = edge.dashes === true;
        return {
            id: edge.id,
            color: isClosed ? COLOR_EDGE_CLOSED : COLOR_EDGE_OPEN,
            width: 2
        };
    });
    edgesDataSet.update(updatedEdges);
    
    network.fit({ animation: { duration: 1000, easingFunction: 'easeInOutQuad' }});
}

// 启动
window.onload = loadData;
