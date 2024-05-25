document.addEventListener('DOMContentLoaded', function() {
    const ws = new WebSocket(`ws://${window.location.hostname}:${window.location.port}`);
  
    ws.onmessage = function(event) {
      const data = JSON.parse(event.data);
      updateCharts(data);
    };
  
    const accelerometerChart = createLineChart('accelerometerChart', 'Accelerometer Data', [
      { label: 'X', borderColor: 'red', fill: false },
      { label: 'Y', borderColor: 'green', fill: false },
      { label: 'Z', borderColor: 'blue', fill: false }
    ]);
  
    const metallicPresenceChart = createBarChart('metallicPresenceChart', 'Metallic Presence', 'purple');
  
    const magnetometerChart = createLineChart('magnetometerChart', 'Magnetometer Data', [
      { label: 'Magnetometer', borderColor: 'orange', fill: false }
    ]);
  
    const uvSensorChart = createLineChart('uvSensorChart', 'UV Sensor Data', [
      { label: 'UV Distance', borderColor: 'violet', fill: false }
    ]);
  
    function updateCharts(data) {
      if (data.accelerometer) {
        const { ax, ay, az } = data.accelerometer;
        updateChart(accelerometerChart, [ax, ay, az]);
      }
  
      if (data.gyroscope) {
        const { gx, gy, gz } = data.gyroscope;
        updateChart(gyroscopeChart, [gx, gy, gz]);
      }
  
      if (data.magnetometer) {
        const { mx, my, mz } = data.magnetometer;
        updateChart(magnetometerChart, [mx, my, mz]);
      }
  
      if (data.ultrasonic) {
        const { distance } = data.ultrasonic;
        updateChart(uvSensorChart, [distance]);
  
        const uvAlert = document.getElementById('uvAlert');
        if (distance > 200) {
          uvAlert.style.display = 'block';
          uvAlert.textContent = `Alert: Height exceeds 2 meters! Current height: ${distance.toFixed(2)} meters.`;
        } else {
          uvAlert.style.display = 'none';
        }
      }
  
      if (typeof data.metallicPresence !== 'undefined') {
        updateChart(metallicPresenceChart, [data.metallicPresence]);
      }
    }
  
    function createLineChart(id, title, datasets) {
      return new Chart(document.getElementById(id), {
        type: 'line',
        data: {
          labels: [],
          datasets: datasets
        },
        options: {
          responsive: true,
          maintainAspectRatio: false,
          scales: {
            x: {
              type: 'time',
              time: {
                unit: 'second'
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
  
    function createBarChart(id, title, backgroundColor) {
      return new Chart(document.getElementById(id), {
        type: 'bar',
        data: {
          labels: [],
          datasets: [{
            label: title,
            data: [],
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
                unit: 'second'
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
  
    function updateChart(chart, dataArrays) {
      chart.data.labels.push(Date.now());
      chart.data.datasets.forEach((dataset, index) => {
        dataset.data.push(dataArrays[index]);
      });
      chart.update();
    }
  });
  