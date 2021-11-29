import React, { useEffect, useMemo, useState } from "react";
import dynamic from "next/dynamic";
import Plot from "react-plotly.js";
import { Slider } from "@mui/material";
import Head from "next/head";

const Plot = dynamic(() => import("react-plotly.js"), { ssr: false });

function setupModule() {
  var Module = {
    preRun: [],
    postRun: [],
    print: (function () {
      var element = document.getElementById("output");
      //   if (element) element.value = ""; // clear browser cache
      return function (text) {
        if (arguments.length > 1)
          text = Array.prototype.slice.call(arguments).join(" ");
        // These replacements are necessary if you render to raw HTML
        //text = text.replace(/&/g, "&amp;");
        //text = text.replace(/</g, "&lt;");
        //text = text.replace(/>/g, "&gt;");
        //text = text.replace('\n', '<br>', 'g');
        console.log(text);
        if (element) {
          //   element.value += text + "\n";
          element.scrollTop = element.scrollHeight; // focus on bottom
        }
      };
    })(),
    printErr: function (text) {
      //   if (arguments.length > 1)
      //     text = Array.prototype.slice.call(arguments).join(" ");
      //   if (0) {
      //     // XXX disabled for safety typeof dump == 'function') {
      //     dump(text + "\n"); // fast, straight to the real console
      //   } else {
      //     console.error(text);
      //   }
    },
    setStatus: function (text) {
      //   if (!Module.setStatus.last)
      //     Module.setStatus.last = { time: Date.now(), text: "" };
      //   if (text === Module.setStatus.text) return;
      //   var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
      //   var now = Date.now();
      //   if (m && now - Date.now() < 30) return; // if this is a progress update, skip it if too soon
      //   if (m) {
      //     text = m[1];
      //     progressElement.value = parseInt(m[2]) * 100;
      //     progressElement.max = parseInt(m[4]) * 100;
      //     progressElement.hidden = false;
      //     spinnerElement.hidden = false;
      //   } else {
      //     progressElement.value = null;
      //     progressElement.max = null;
      //     progressElement.hidden = true;
      //     if (!text) spinnerElement.hidden = true;
      //   }
      //   statusElement.innerHTML = text;
      // },
      // totalDependencies: 0,
      // monitorRunDependencies: function (left) {
      //   this.totalDependencies = Math.max(this.totalDependencies, left);
      //   Module.setStatus(
      //     left
      //       ? "Preparing... (" +
      //           (this.totalDependencies - left) +
      //           "/" +
      //           this.totalDependencies +
      //           ")"
      //       : "All downloads complete."
      //   );
    },
  };
  Module.setStatus("Downloading...");
  window.onerror = function () {
    Module.setStatus("Exception thrown, see JavaScript console");

    Module.setStatus = function (text) {
      if (text) Module.printErr("[post-exception status] " + text);
    };
  };

  return Module;
}

const LowtranDemo = () => {
  const [module, setModule] = useState(null);
  const [model, setModel] = useState(1);

  const [height1, setHeight1] = useState(5);
  const [height2, setHeight2] = useState(10);

  const [range, setRange] = useState(10);

  useEffect(() => {
    setModule(setupModule());
  }, []);

  const data = useMemo(() => {
    if (typeof window === "undefined" || window["Module"] == null) {
      return;
    }
    let module = window["Module"];
    // console.log(window["Module"]);
    var result = window["Module"].runLowtran(model, 2, height1, height2, range);

    console.log("New range", range);
    // console.log(" JS side pointer: " + result[0] + " size: " + result[1]);

    let xs = [];
    let ys = [];

    for (var i = 0; i < result[1]; i++) {
      let val = module.HEAPF32[(result[0] + i * 4) / 4];

      if (i % 2 === 0) {
        xs.push(val);
      } else {
        ys.push(val);
      }
    }

    module._free(result[0]);
    return { x: xs, y: ys };
  }, [module, model, height1, height2, range]);

  return (
    <div style={{ width: "100%", height: "100%" }}>
      <Head>
        <script src="/a.out.js"></script>
      </Head>
      <div style={{ width: "50%" }}>
        <Plot
          data={[data]}
          layout={{ width: 560, height: 480, title: "Lowtran" }}
        ></Plot>
      </div>
      <div
        style={{ width: "50%", height: "100%", backgroundColor: "lightgray" }}
      >
        Model:
        <Slider
          onChange={(ev, newModelI) => setModel(Number(newModelI))}
          defaultValue={1}
          min={0}
          max={5}
          step={1}
        />
        Height 1:
        <Slider
          onChange={(ev, newHeight1) => setHeight1(Number(newHeight1))}
          defaultValue={5}
          min={0}
          max={60}
        />
        Height 2:
        <Slider
          onChange={(ev, newHeight2) => setHeight2(Number(newHeight2))}
          defaultValue={10}
          min={0}
          max={60}
        />
        Range:
        <Slider
          onChange={(ev, newRange) => setRange(Number(newRange))}
          defaultValue={10}
          min={Math.abs(height2 - height1)}
          max={60}
        />
      </div>
    </div>
  );
};

export default LowtranDemo;
