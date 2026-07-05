tailwind.config = {
    theme: {
        extend: {
            fontFamily: {
                mono: ['"JetBrains Mono"', 'monospace'],
                sans: ['Inter', 'system-ui', 'sans-serif'],
            },
            colors: {
                platinum: {
                    50: '#f8f8f7',
                    100: '#f0efee',
                    200: '#e5e4e2',
                    300: '#d4d2cf',
                    400: '#b8b5b0',
                    500: '#9a9590',
                    600: '#7d7873',
                    700: '#5c5854',
                    800: '#3d3a37',
                    900: '#1f1e1c',
                    950: '#0f0f0e',
                },
                accent: {
                    cyan: '#22d3ee',
                    emerald: '#34d399',
                    amber: '#fbbf24',
                    rose: '#fb7185',
                    violet: '#a78bfa',
                }
            },
            animation: {
                'cursor-blink': 'blink 1s step-end infinite',
                'fade-in-up': 'fadeInUp 0.8s ease-out forwards',
                'glow': 'glow 2s ease-in-out infinite alternate',
            },
            keyframes: {
                blink: {
                    '0%, 100%': { opacity: '1' },
                    '50%': { opacity: '0' },
                },
                fadeInUp: {
                    '0%': { opacity: '0', transform: 'translateY(20px)' },
                    '100%': { opacity: '1', transform: 'translateY(0)' },
                },
                glow: {
                    '0%': { boxShadow: '0 0 20px rgba(34, 211, 238, 0.1)' },
                    '100%': { boxShadow: '0 0 40px rgba(34, 211, 238, 0.3)' },
                },
            }
        }
    }
}

document.addEventListener('DOMContentLoaded', function() {
    
    fetch('assets/res/update.json')
        .then(response => response.json())
        .then(data => renderChangelog(data))
        .catch(err => {
            console.error('Failed to load changelog:', err);
            document.getElementById('changelog-container').innerHTML = 
                '<p class="text-platinum-500 text-center">加载更新日志失败</p>';
        });

    // Mobile menu toggle (existing code)
    const menuBtn = document.getElementById('menuBtn');
    const mobileMenu = document.getElementById('mobileMenu');
    const menuIcon = document.getElementById('menuIcon');
    const closeIcon = document.getElementById('closeIcon');

    if (menuBtn) {
        menuBtn.addEventListener('click', () => {
            mobileMenu.classList.toggle('hidden');
            menuIcon.classList.toggle('hidden');
            closeIcon.classList.toggle('hidden');
        });

        mobileMenu.querySelectorAll('a').forEach(link => {
            link.addEventListener('click', () => {
                mobileMenu.classList.add('hidden');
                menuIcon.classList.remove('hidden');
                closeIcon.classList.add('hidden');
            });
        });
    }
});

function renderChangelog(data) {
    const container = document.getElementById('changelog-container');
    const timelineLine = container.querySelector('.absolute');
    container.innerHTML = '';
    container.appendChild(timelineLine);

    data.forEach((item, index) => {
        const isFirst = index === 0;
        const isEven = index % 2 === 0;
        const tagStr = item.tag.join('.');
        const vNum = item.tag[0];
        
        const infoHtml = item.info.map(([type, desc]) => {
            const colorClass = {
                'FIX': 'text-accent-emerald',
                'ADD': 'text-accent-cyan',
                'DEL': 'text-accent-rose',
                'UPD': 'text-accent-amber'
            }[type] || 'text-platinum-400';
            return `<li class="flex items-start gap-2"><span class="${colorClass} shrink-0">[${type}]</span><span>${escapeHtml(desc)}</span></li>`;
        }).join('');

        const cardHtml = `
            <div class="code-block rounded-xl p-5">
                <div class="${isFirst ? 'text-accent-emerald' : 'text-platinum-300'} font-mono text-sm font-bold mb-2">${escapeHtml(item.version)}</div>
                <div class="text-platinum-500 text-sm mb-3">${tagStr}</div>
                <ul class="text-platinum-400 text-sm space-y-1">${infoHtml}</ul>
            </div>
        `;

        const dotHtml = `
            <div class="w-8 h-8 rounded-full ${isFirst ? 'bg-accent-emerald/20 border-accent-emerald' : 'bg-platinum-700 border-platinum-600'} border-2 flex items-center justify-center shrink-0 z-10">
                <span class="${isFirst ? 'text-accent-emerald' : 'text-platinum-400'} text-xs font-bold">v${vNum}</span>
            </div>
        `;

        const entry = document.createElement('div');
        entry.className = 'relative flex items-start gap-4 md:gap-0';

        if (isEven) {
            // 偶数：卡片在左，圆点在中，右侧空
            entry.innerHTML = `
                <div class="w-full md:w-1/2 md:pr-8">
                    ${cardHtml}
                </div>
                <div class="hidden md:flex md:w-0 md:justify-center">
                    ${dotHtml}
                </div>
                <div class="md:w-1/2 md:pl-8"></div>
            `;
        } else {
            // 奇数：左侧空，圆点在中，卡片在右
            entry.innerHTML = `
                <div class="hidden md:block md:w-1/2 md:pr-8"></div>
                <div class="hidden md:flex md:w-0 md:justify-center">
                    ${dotHtml}
                </div>
                <div class="w-full md:w-1/2 md:pl-8">
                    ${cardHtml}
                </div>
            `;
        }

        // 移动端：圆点 + 卡片都在左侧
        const mobileDot = document.createElement('div');
        mobileDot.className = 'md:hidden flex items-start gap-4';
        mobileDot.innerHTML = `${dotHtml}${cardHtml}`;
        
        // 替换 entry 为移动端版本（包含桌面端结构）
        entry.innerHTML = '';
        entry.appendChild(mobileDot);
        
        // 桌面端结构
        const desktopWrap = document.createElement('div');
        desktopWrap.className = 'hidden md:flex w-full items-start';
        if (isEven) {
            desktopWrap.innerHTML = `
                <div class="w-1/2 pr-8">${cardHtml}</div>
                <div class="relative flex justify-center" style="width:0">${dotHtml}</div>
                <div class="w-1/2 pl-8"></div>
            `;
        } else {
            desktopWrap.innerHTML = `
                <div class="w-1/2 pr-8"></div>
                <div class="relative flex justify-center" style="width:0">${dotHtml}</div>
                <div class="w-1/2 pl-8">${cardHtml}</div>
            `;
        }
        entry.appendChild(desktopWrap);

        container.appendChild(entry);
    });
}

function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
}