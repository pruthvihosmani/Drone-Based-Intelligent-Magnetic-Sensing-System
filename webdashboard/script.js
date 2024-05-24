document.addEventListener('DOMContentLoaded', function() {
    const refreshInterval = 5000; // Refresh interval in milliseconds (5 seconds)
    
    function generateDummyData() {
      const data = [];
      for (let i = 0; i < 10; i++) {
        data.push({
          timestamp: new Date(Date.now() - i * 60000).toISOString(), // Generate timestamps 1 minute apart
          accel_x: Math.random() * 10, // Random accelerometer X-axis data
          accel_y: Math.random() * 10, // Random accelerometer Y-axis data
          accel_z: Math.random() * 10, // Random accelerometer Z-axis data
          metallic_presence: Math.random() > 0.5 ? 1 : 0, // Random binary data for metallic presence
          magnetometer: Math.random() * 10, // Random magnetometer data
          uv_distance: Math.random() * 5, // Random UV sensor distance data
          battery_level: Math.random() * 100, // Random battery level data
          sensor_status: JSON.stringify([ // Random sensor status
            { sensor: 'Sensor 1', status: 'OK' },
            { sensor: 'Sensor 2', status: 'OK' },
            { sensor: 'Sensor 3', status: 'OK' }
          ])
        });
      }
      return data;
    }
  
    // Initialize charts
    let accelerometerChart, metallicPresenceChart, magnetometerChart, uvSensorChart, batteryLevelChart;
    
    function initializeCharts() {
      const dummyData = generateDummyData();
  
      const timestamps = dummyData.map(item => item.timestamp);
      const accelX = dummyData.map(item => item.accel_x);
      const accelY = dummyData.map(item => item.accel_y);
      const accelZ = dummyData.map(item => item.accel_z);
      const metallicPresence = dummyData.map(item => item.metallic_presence);
      const magnetometer = dummyData.map(item => item.magnetometer);
      const uvDistance = dummyData.map(item => item.uv_distance);
      const batteryLevel = dummyData.map(item => item.battery_level);
      const sensorStatus = JSON.parse(dummyData[dummyData.length - 1].sensor_status);
  
      accelerometerChart = createLineChart('accelerometerChart', 'Accelerometer Data', timestamps, [
        { label: 'X', data: accelX, borderColor: 'red', fill: false },
        { label: 'Y', data: accelY, borderColor: 'green', fill: false },
        { label: 'Z', data: accelZ, borderColor: 'blue', fill: false }
      ]);
  
      metallicPresenceChart = createBarChart('metallicPresenceChart', 'Metallic Presence', timestamps, metallicPresence, 'purple');
  
      magnetometerChart = createLineChart('magnetometerChart', 'Magnetometer Data', timestamps, [
        { label: 'Magnetometer', data: magnetometer, borderColor: 'orange', fill: false }
      ]);
  
      uvSensorChart = createLineChart('uvSensorChart', 'UV Sensor Data', timestamps, [
        { label: 'UV Distance', data: uvDistance, borderColor: 'violet', fill: false }
      ]);
  
      batteryLevelChart = createLineChart('batteryLevelChart', 'Battery Level', timestamps, [
        { label: 'Battery Level', data: batteryLevel, borderColor: 'green', fill: false }
      ]);
  
      // Display sensor status list
      const sensorStatusList = document.getElementById('sensorStatusList');
      sensorStatusList.innerHTML = '';
      sensorStatus.forEach(status => {
        const li = document.createElement('li');
        li.textContent = `${status.sensor}: ${status.status}`;
        sensorStatusList.appendChild(li);
      });
  
      // Display alert if UV distance exceeds 2 meters
      const uvAlert = document.getElementById('uvAlert');
      if (uvDistance.some(distance => distance > 2)) {
        uvAlert.style.display = 'block';
        uvAlert.textContent = `Alert: Height exceeds 2 meters! Current height: ${Math.max(...uvDistance).toFixed(2)} meters.`;
      } else {
        uvAlert.style.display = 'none';
      }
    }
  
    function refreshCharts() {
      const dummyData = generateDummyData();
  
      const timestamps = dummyData.map(item => item.timestamp);
      const accelX = dummyData.map(item => item.accel_x);
      const accelY = dummyData.map(item => item.accel_y);
      const accelZ = dummyData.map(item => item.accel_z);
      const metallicPresence = dummyData.map(item => item.metallic_presence);
      const magnetometer = dummyData.map(item => item.magnetometer);
      const uvDistance = dummyData.map(item => item.uv_distance);
      const batteryLevel = dummyData.map(item => item.battery_level);
      const sensorStatus = JSON.parse(dummyData[dummyData.length - 1].sensor_status);
  
      updateChart(accelerometerChart, timestamps, [accelX, accelY, accelZ]);
      updateChart(metallicPresenceChart, timestamps, [metallicPresence]);
      updateChart(magnetometerChart, timestamps, [magnetometer]);
      updateChart(uvSensorChart, timestamps, [uvDistance]);
      updateChart(batteryLevelChart, timestamps, [batteryLevel]);
  
      // Update sensor status list
      const sensorStatusList = document.getElementById('sensorStatusList');
      sensorStatusList.innerHTML = '';
      sensorStatus.forEach(status => {
        const li = document.createElement('li');
        li.textContent = `${status.sensor}: ${status.status}`;
        sensorStatusList.appendChild(li);
      });
  
      // Update alert if UV distance exceeds 2 meters
      const uvAlert = document.getElementById('uvAlert');
      if (uvDistance.some(distance => distance > 2)) {
        uvAlert.style.display = 'block';
        uvAlert.textContent = `Alert: Height exceeds 2 meters! Current height: ${Math.max(...uvDistance).toFixed(2)} meters.`;
      } else {
        uvAlert.style.display = 'none';
      }
    }
  
    function createLineChart(id, title, labels, datasets) {
      return new Chart(document.getElementById(id), {
        type: 'line',
        data: {
          labels: labels,
          datasets: datasets
        },
        options: {
          responsive: true,
          maintainAspectRatio: false,
          scales: {
            x: {
              type: 'time',
              time: {
                unit: 'minute'
              }
            },
            y: {
              beginAtZero: true
            }
          },
          plugins: {
            title: {
              display: true,
              text: title
            },
            tooltip: {
              callbacks: {
                label: function(context) {
                  return context.dataset.label + ': ' + context.parsed.y.toFixed(2);
                }
              }
            }
          }
        }
      });
    }
  
    function createBarChart(id, title, labels, data, backgroundColor) {
      return new Chart(document.getElementById(id), {
        type: 'bar',
        data: {
          labels: labels,
          datasets: [{
            label: title,
            data: data,
            backgroundColor: backgroundColor
          }]
        },
        options: {
          responsive: true,
          maintainAspectRatio: false,
          scales: {
            x: {
              type: 'time',
              time: {
                unit: 'minute'
              }
            },
            y: {
              beginAtZero: true
            }
          },
          plugins: {
            title: {
              display: true,
              text: title
            },
            tooltip: {
              callbacks: {
                label: function(context) {
                  return context.dataset.label + ': ' + context.parsed.y;
                }
              }
            }
          }
        }
      });
    }
  
    function updateChart(chart, labels, dataArrays) {
      chart.data.labels = labels;
      chart.data.datasets.forEach((dataset, index) => {
        dataset.data = dataArrays[index];
      });
      chart.update();
    }
  
    initializeCharts();
    setInterval(refreshCharts, refreshInterval);
  });
  