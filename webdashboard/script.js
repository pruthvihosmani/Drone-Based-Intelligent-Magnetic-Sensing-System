document.addEventListener('DOMContentLoaded', function() {
    // Function to generate dummy data
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
  
    // Generate dummy data
    const dummyData = generateDummyData();
  
    // Extract data for charts
    const timestamps = dummyData.map(item => item.timestamp);
    const accelX = dummyData.map(item => item.accel_x);
    const accelY = dummyData.map(item => item.accel_y);
    const accelZ = dummyData.map(item => item.accel_z);
    const metallicPresence = dummyData.map(item => item.metallic_presence);
    const magnetometer = dummyData.map(item => item.magnetometer);
    const uvDistance = dummyData.map(item => item.uv_distance);
    const batteryLevel = dummyData.map(item => item.battery_level);
    const sensorStatus = JSON.parse(dummyData[dummyData.length - 1].sensor_status);
  
    // Function to create line chart
    function createLineChart(id, title, labels, datasets) {
      new Chart(document.getElementById(id), {
        type: 'line',
        data: {
          labels: labels,
          datasets: datasets
        },
        options: {
          responsive: true,
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
  
    // Function to create bar chart
    function createBarChart(id, title, labels, data, backgroundColor) {
      new Chart(document.getElementById(id), {
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
  
    // Create charts with dummy data
    createLineChart('accelerometerChart', 'Accelerometer Data', timestamps, [
      { label: 'X', data: accelX, borderColor: 'red', fill: false },
      { label: 'Y', data: accelY, borderColor: 'green', fill: false },
      { label: 'Z', data: accelZ, borderColor: 'blue', fill: false }
    ]);
  
    createBarChart('metallicPresenceChart', 'Metallic Presence', timestamps, metallicPresence, 'purple');
  
    createLineChart('magnetometerChart', 'Magnetometer Data', timestamps, [
      { label: 'Magnetometer', data: magnetometer, borderColor: 'orange', fill: false }
    ]);
  
    createLineChart('uvSensorChart', 'UV Sensor Data', timestamps, [
      { label: 'UV Distance', data: uvDistance, borderColor: 'violet', fill: false }
    ]);
  
    // Display alert if UV distance exceeds 2 meters
    if (uvDistance.some(distance => distance > 2)) {
      document.getElementById('uvAlert').style.display = 'block';
    }
  
    createLineChart('batteryLevelChart', 'Battery Level', timestamps, [
      { label: 'Battery Level', data: batteryLevel, borderColor: 'green', fill: false }
    ]);
  
    // Display sensor status list
    const sensorStatusList = document.getElementById('sensorStatusList');
    sensorStatus.forEach(status => {
      const li = document.createElement('li');
      li.textContent = `${status.sensor}: ${status.status}`;
      sensorStatusList.appendChild(li);
    });
  });
  