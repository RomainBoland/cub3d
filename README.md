<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Raycasting Math Explained</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: #1a1a1a;
            color: #fff;
            margin: 0;
            padding: 20px;
            line-height: 1.6;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        .section {
            background: #2a2a2a;
            margin: 20px 0;
            padding: 20px;
            border-radius: 10px;
            border: 2px solid #444;
        }
        .canvas-container {
            display: flex;
            gap: 20px;
            flex-wrap: wrap;
            justify-content: center;
            margin: 20px 0;
        }
        canvas {
            border: 2px solid #555;
            background: #000;
        }
        .math-box {
            background: #1a3a1a;
            padding: 15px;
            border-radius: 5px;
            font-family: monospace;
            border: 1px solid #4a6a4a;
            margin: 10px 0;
        }
        .key-point {
            background: #3a1a1a;
            padding: 15px;
            border-left: 4px solid #ff6666;
            border-radius: 5px;
            margin: 10px 0;
        }
        h1, h2 {
            color: #66ccff;
        }
        .highlight {
            color: #ffaa00;
            font-weight: bold;
        }
        .interactive {
            text-align: center;
            margin: 20px 0;
        }
        input[type="range"] {
            width: 300px;
            margin: 10px;
        }
        .angle-display {
            font-size: 1.2em;
            color: #ffaa00;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🧮 Raycasting Math - Trigonometry Made Simple</h1>
        
        <div class="section">
            <h2>📐 Basic Trigonometry Refresher</h2>
            <div class="canvas-container">
                <canvas id="trigCanvas" width="400" height="400"></canvas>
            </div>
            
            <div class="key-point">
                <strong>Key Concept:</strong> Angles tell us direction, sin/cos convert angles to movement!
            </div>
            
            <div class="math-box">
                <strong>The Magic Formulas:</strong><br>
                • cos(angle) = horizontal movement<br>
                • sin(angle) = vertical movement<br><br>
                
                <strong>Examples:</strong><br>
                • Angle 0° (East): cos(0) = 1, sin(0) = 0 → Move right<br>
                • Angle 90° (South): cos(90) = 0, sin(90) = 1 → Move down<br>
                • Angle 180° (West): cos(180) = -1, sin(180) = 0 → Move left<br>
                • Angle 270° (North): cos(270) = 0, sin(270) = -1 → Move up
            </div>
        </div>

        <div class="section">
            <h2>🎯 Interactive Ray Direction</h2>
            <div class="interactive">
                <label>Ray Angle: <span class="angle-display" id="angleDisplay">0°</span></label><br>
                <input type="range" id="angleSlider" min="0" max="360" value="0"><br>
                <div>cos(angle) = <span id="cosValue">1.00</span></div>
                <div>sin(angle) = <span id="sinValue">0.00</span></div>
            </div>
            <div class="canvas-container">
                <canvas id="interactiveCanvas" width="400" height="400"></canvas>
            </div>
        </div>

        <div class="section">
            <h2>📏 Distance Calculation (The Hardest Part)</h2>
            <div class="canvas-container">
                <canvas id="distanceCanvas" width="500" height="400"></canvas>
            </div>
            
            <div class="math-box">
                <strong>Why This Math Works:</strong><br><br>
                
                If ray_dir_x = 0.6 and ray_dir_y = 0.8:<br>
                • delta_dist_x = |1 / 0.6| = 1.67<br>
                • delta_dist_y = |1 / 0.8| = 1.25<br><br>
                
                <strong>What this means:</strong><br>
                • To move 1 unit in X: ray travels 1.67 total units<br>
                • To move 1 unit in Y: ray travels 1.25 total units<br><br>
                
                <strong>Why?</strong> Because the ray is diagonal!
            </div>
            
            <div class="key-point">
                <strong>Think of it like this:</strong><br>
                If you walk diagonally across a city block, you walk further than just going straight across. The delta_dist tells us "how much further" for each direction.
            </div>
        </div>

        <div class="section">
            <h2>🔄 Step-by-Step DDA Process</h2>
            <div class="canvas-container">
                <canvas id="ddaStepCanvas" width="500" height="400"></canvas>
            </div>
            
            <div class="math-box">
                <strong>DDA Loop Logic:</strong><br><br>
                
                1. <span class="highlight">side_dist_x</span> = distance to next vertical line<br>
                2. <span class="highlight">side_dist_y</span> = distance to next horizontal line<br>
                3. Compare: which is closer?<br>
                4. Jump to the closer one<br>
                5. Check if that grid square has a wall<br>
                6. If no wall, repeat from step 3<br><br>
                
                <strong>The Magic:</strong> We only check grid intersections, not every point!
            </div>
        </div>

        <div class="section">
            <h2>📺 Field of View (FOV) Math</h2>
            <div class="canvas-container">
                <canvas id="fovCanvas" width="500" height="400"></canvas>
            </div>
            
            <div class="math-box">
                <strong>Field of View Calculation:</strong><br><br>
                
                For screen column X (0 to 1920):<br>
                1. camera_x = 2 * x / 1920 - 1  // Range: -1 to +1<br>
                2. ray_angle = player_angle + atan(camera_x * tan(FOV/2))<br><br>
                
                <strong>Why?</strong><br>
                • FOV/2 = half the field of view (usually 30°)<br>
                • camera_x goes from -1 to +1 across screen<br>
                • This creates a smooth angle spread
            </div>
            
            <div class="key-point">
                <strong>Simple Version:</strong> Each screen column gets a slightly different ray angle. Left side = player_angle - 30°, right side = player_angle + 30°
            </div>
        </div>

        <div class="section">
            <h2>🎨 Putting It All Together</h2>
            <div class="math-box">
                <strong>The Complete Process:</strong><br><br>
                
                1. <span class="highlight">For each screen column (x):</span><br>
                &nbsp;&nbsp;&nbsp;• Calculate ray angle for that column<br>
                &nbsp;&nbsp;&nbsp;• Convert angle to ray direction (cos/sin)<br><br>
                
                2. <span class="highlight">Cast the ray using DDA:</span><br>
                &nbsp;&nbsp;&nbsp;• Jump from grid line to grid line<br>
                &nbsp;&nbsp;&nbsp;• Stop when hitting a wall<br>
                &nbsp;&nbsp;&nbsp;• Return distance to that wall<br><br>
                
                3. <span class="highlight">Convert distance to wall height:</span><br>
                &nbsp;&nbsp;&nbsp;• wall_height = SCREEN_HEIGHT / distance<br>
                &nbsp;&nbsp;&nbsp;• Draw vertical line on screen<br><br>
                
                <strong>Result:</strong> 1920 vertical lines = 3D view!
            </math-box>
        </div>
    </div>

    <script>
        // Trigonometry visualization
        const trigCanvas = document.getElementById('trigCanvas');
        const trigCtx = trigCanvas.getContext('2d');
        
        function drawTrig() {
            trigCtx.fillStyle = '#000';
            trigCtx.fillRect(0, 0, 400, 400);
            
            const centerX = 200, centerY = 200;
            const radius = 150;
            
            // Draw circle
            trigCtx.strokeStyle = '#444';
            trigCtx.beginPath();
            trigCtx.arc(centerX, centerY, radius, 0, Math.PI * 2);
            trigCtx.stroke();
            
            // Draw axes
            trigCtx.strokeStyle = '#666';
            trigCtx.beginPath();
            trigCtx.moveTo(50, centerY);
            trigCtx.lineTo(350, centerY);
            trigCtx.moveTo(centerX, 50);
            trigCtx.lineTo(centerX, 350);
            trigCtx.stroke();
            
            // Draw angle examples
            const angles = [0, Math.PI/2, Math.PI, 3*Math.PI/2];
            const labels = ['0° (E)', '90° (S)', '180° (W)', '270° (N)'];
            
            angles.forEach((angle, i) => {
                const x = centerX + Math.cos(angle) * radius;
                const y = centerY + Math.sin(angle) * radius;
                
                // Draw line
                trigCtx.strokeStyle = '#ff6666';
                trigCtx.lineWidth = 2;
                trigCtx.beginPath();
                trigCtx.moveTo(centerX, centerY);
                trigCtx.lineTo(x, y);
                trigCtx.stroke();
                
                // Draw point
                trigCtx.fillStyle = '#ffaa00';
                trigCtx.beginPath();
                trigCtx.arc(x, y, 5, 0, Math.PI * 2);
                trigCtx.fill();
                
                // Label
                trigCtx.fillStyle = '#fff';
                trigCtx.font = '12px Arial';
                trigCtx.fillText(labels[i], x - 20, y - 10);
            });
            
            // Labels
            trigCtx.fillStyle = '#fff';
            trigCtx.font = '14px Arial';
            trigCtx.fillText('cos(angle) = X movement', 10, 30);
            trigCtx.fillText('sin(angle) = Y movement', 10, 50);
        }
        
        // Interactive canvas
        const interactiveCanvas = document.getElementById('interactiveCanvas');
        const intCtx = interactiveCanvas.getContext('2d');
        const angleSlider = document.getElementById('angleSlider');
        const angleDisplay = document.getElementById('angleDisplay');
        const cosValue = document.getElementById('cosValue');
        const sinValue = document.getElementById('sinValue');
        
        function updateInteractive() {
            const angleDeg = parseInt(angleSlider.value);
            const angleRad = angleDeg * Math.PI / 180;
            
            angleDisplay.textContent = angleDeg + '°';
            cosValue.textContent = Math.cos(angleRad).toFixed(2);
            sinValue.textContent = Math.sin(angleRad).toFixed(2);
            
            // Clear and redraw
            intCtx.fillStyle = '#000';
            intCtx.fillRect(0, 0, 400, 400);
            
            const centerX = 200, centerY = 200;
            const radius = 150;
            
            // Draw circle and axes
            intCtx.strokeStyle = '#444';
            intCtx.beginPath();
            intCtx.arc(centerX, centerY, radius, 0, Math.PI * 2);
            intCtx.stroke();
            
            intCtx.strokeStyle = '#666';
            intCtx.beginPath();
            intCtx.moveTo(50, centerY);
            intCtx.lineTo(350, centerY);
            intCtx.moveTo(centerX, 50);
            intCtx.lineTo(centerX, 350);
            intCtx.stroke();
            
            // Draw current angle
            const x = centerX + Math.cos(angleRad) * radius;
            const y = centerY + Math.sin(angleRad) * radius;
            
            intCtx.strokeStyle = '#00ff00';
            intCtx.lineWidth = 3;
            intCtx.beginPath();
            intCtx.moveTo(centerX, centerY);
            intCtx.lineTo(x, y);
            intCtx.stroke();
            
            // Draw components
            intCtx.strokeStyle = '#ff6666';
            intCtx.lineWidth = 2;
            intCtx.setLineDash([5, 5]);
            intCtx.beginPath();
            intCtx.moveTo(centerX, centerY);
            intCtx.lineTo(x, centerY);
            intCtx.moveTo(x, centerY);
            intCtx.lineTo(x, y);
            intCtx.stroke();
            intCtx.setLineDash([]);
            
            // Point
            intCtx.fillStyle = '#ffaa00';
            intCtx.beginPath();
            intCtx.arc(x, y, 6, 0, Math.PI * 2);
            intCtx.fill();
            
            // Labels
            intCtx.fillStyle = '#fff';
            intCtx.font = '12px Arial';
            intCtx.fillText(`cos = ${Math.cos(angleRad).toFixed(2)}`, x + 10, y - 10);
            intCtx.fillText(`sin = ${Math.sin(angleRad).toFixed(2)}`, x + 10, y + 5);
        }
        
        angleSlider.addEventListener('input', updateInteractive);
        
        // Distance visualization
        const distCanvas = document.getElementById('distanceCanvas');
        const distCtx = distCanvas.getContext('2d');
        
        function drawDistance() {
            distCtx.fillStyle = '#000';
            distCtx.fillRect(0, 0, 500, 400);
            
            // Draw grid
            distCtx.strokeStyle = '#333';
            distCtx.lineWidth = 1;
            for (let i = 0; i <= 500; i += 50) {
                distCtx.beginPath();
                distCtx.moveTo(i, 0);
                distCtx.lineTo(i, 400);
                distCtx.stroke();
            }
            for (let i = 0; i <= 400; i += 50) {
                distCtx.beginPath();
                distCtx.moveTo(0, i);
                distCtx.lineTo(500, i);
                distCtx.stroke();
            }
            
            // Draw ray
            const startX = 100, startY = 200;
            const angle = Math.PI / 6; // 30 degrees
            const endX = 400, endY = startY + Math.tan(angle) * (endX - startX);
            
            distCtx.strokeStyle = '#00ff00';
            distCtx.lineWidth = 3;
            distCtx.beginPath();
            distCtx.moveTo(startX, startY);
            distCtx.lineTo(endX, endY);
            distCtx.stroke();
            
            // Mark grid intersections
            for (let x = startX + 50; x < endX; x += 50) {
                const y = startY + Math.tan(angle) * (x - startX);
                distCtx.fillStyle = '#ff6666';
                distCtx.beginPath();
                distCtx.arc(x, y, 4, 0, Math.PI * 2);
                distCtx.fill();
            }
            
            // Labels
            distCtx.fillStyle = '#fff';
            distCtx.font = '14px Arial';
            distCtx.fillText('Ray jumps from grid line to grid line', 10, 30);
            distCtx.fillText('Red dots = DDA check points', 10, 50);
            distCtx.fillText('Much faster than checking every pixel!', 10, 70);
        }
        
        // DDA step visualization
        const ddaCanvas = document.getElementById('ddaStepCanvas');
        const ddaCtx = ddaCanvas.getContext('2d');
        
        function drawDDASteps() {
            ddaCtx.fillStyle = '#000';
            ddaCtx.fillRect(0, 0, 500, 400);
            
            // Draw grid
            ddaCtx.strokeStyle = '#333';
            for (let i = 0; i <= 500; i += 50) {
                ddaCtx.beginPath();
                ddaCtx.moveTo(i, 0);
                ddaCtx.lineTo(i, 400);
                ddaCtx.stroke();
            }
            for (let i = 0; i <= 400; i += 50) {
                ddaCtx.beginPath();
                ddaCtx.moveTo(0, i);
                ddaCtx.lineTo(500, i);
                ddaCtx.stroke();
            }
            
            // Simulate DDA steps
            const startX = 75, startY = 75;
            const rayDirX = 0.6, rayDirY = 0.4;
            
            ddaCtx.fillStyle = '#00ff00';
            ddaCtx.beginPath();
            ddaCtx.arc(startX, startY, 6, 0, Math.PI * 2);
            ddaCtx.fill();
            
            // Show step progression
            let currentX = startX, currentY = startY;
            let step = 1;
            
            for (let i = 0; i < 6; i++) {
                const nextX = startX + rayDirX * 50 * step;
                const nextY = startY + rayDirY * 50 * step;
                
                ddaCtx.strokeStyle = i < 3 ? '#ffaa00' : '#ff6666';
                ddaCtx.lineWidth = 2;
                ddaCtx.beginPath();
                ddaCtx.moveTo(currentX, currentY);
                ddaCtx.lineTo(nextX, nextY);
                ddaCtx.stroke();
                
                ddaCtx.fillStyle = i < 3 ? '#ffaa00' : '#ff6666';
                ddaCtx.beginPath();
                ddaCtx.arc(nextX, nextY, 4, 0, Math.PI * 2);
                ddaCtx.fill();
                
                ddaCtx.fillStyle = '#fff';
                ddaCtx.font = '12px Arial';
                ddaCtx.fillText(`${i + 1}`, nextX + 8, nextY + 4);
                
                currentX = nextX;
                currentY = nextY;
                step++;
            }
            
            // Wall
            ddaCtx.fillStyle = '#666';
            ddaCtx.fillRect(300, 150, 50, 50);
            
            ddaCtx.fillStyle = '#fff';
            ddaCtx.font = '14px Arial';
            ddaCtx.fillText('DDA jumps from intersection to intersection', 10, 30);
            ddaCtx.fillText('Stops when it hits a wall (gray square)', 10, 50);
        }
        
        // FOV visualization
        const fovCanvas = document.getElementById('fovCanvas');
        const fovCtx = fovCanvas.getContext('2d');
        
        function drawFOV() {
            fovCtx.fillStyle = '#000';
            fovCtx.fillRect(0, 0, 500, 400);
            
            const playerX = 250, playerY = 300;
            const playerAngle = -Math.PI / 2; // Facing up
            const fov = Math.PI / 3; // 60 degrees
            
            // Draw player
            fovCtx.fillStyle = '#ff0000';
            fovCtx.beginPath();
            fovCtx.arc(playerX, playerY, 8, 0, Math.PI * 2);
            fovCtx.fill();
            
            // Draw FOV rays
            for (let i = 0; i < 11; i++) {
                const t = i / 10; // 0 to 1
                const cameraX = 2 * t - 1; // -1 to +1
                const rayAngle = playerAngle + Math.atan(cameraX * Math.tan(fov / 2));
                
                const endX = playerX + Math.cos(rayAngle) * 150;
                const endY = playerY + Math.sin(rayAngle) * 150;
                
                fovCtx.strokeStyle = i === 5 ? '#ffaa00' : '#00ff00';
                fovCtx.lineWidth = i === 5 ? 2 : 1;
                fovCtx.beginPath();
                fovCtx.moveTo(playerX, playerY);
                fovCtx.lineTo(endX, endY);
                fovCtx.stroke();
            }
            
            // Labels
            fovCtx.fillStyle = '#fff';
            fovCtx.font = '14px Arial';
            fovCtx.fillText('Player FOV = 60°', 10, 30);
            fovCtx.fillText('Each ray = one screen column', 10, 50);
            fovCtx.fillText('Yellow ray = center of screen', 10, 70);
        }
        
        // Initialize all visualizations
        drawTrig();
        updateInteractive();
        drawDistance();
        drawDDASteps();
        drawFOV();
    </script>
</body>
</html>