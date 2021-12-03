import React, { useEffect, useMemo, useState } from "react";
import dynamic from "next/dynamic";
import Plot from "react-plotly.js";
import {
  Divider,
  InputLabel,
  MenuItem,
  Select,
  Slider,
  Typography,
} from "@mui/material";
import Head from "next/head";
import { useWindowSize } from "react-use";

const Plot = dynamic(() => import("react-plotly.js"), {
  ssr: false,
}) as React.FC<any>;

enum MODEL {
  USER_SPECIFIED = 0,
  TROPICAL_ATMOSPHERE = 1,
  MIDLATITUDE_SUMMER = 2,
  MIDLATITUDE_WINTER = 3,
  SUBARTIC_SUMMER = 4,
  SUBARTIC_WINTER = 5,
  US_STANDARD_1976 = 6,
  NEW_MODEL = 7,
}

const DEFAULT_MODEL = MODEL.TROPICAL_ATMOSPHERE;
const DISABLED_MODELS = [MODEL.USER_SPECIFIED, MODEL.NEW_MODEL];

enum IHAZE {
  NO_AEROSOL = 0,
  RURAL_EXTINCTION_23 = 1,
  RURAL_EXTINCTION_5 = 2,
  NAVY_MARITIME = 3,
  MARITIME_EXTINCTION = 4,
  URBAN_EXTINCTION = 5,
  TROPOSPHERIC_EXTINCTION = 6,
  USER_DEFINED = 7,
  ADVECTIVE_FOG = 8,
  RADIATIVE_FOG = 9,
  DESERT_EXTINCTION = 10,
}

const DEFAULT_IHAZE = IHAZE.NO_AEROSOL;
const DISABLED_IHAZE = [];

enum ISEASN {
  DEFAULT = 0,
  SPRING_SUMMER = 1,
  FALL_WINTER = 2,
}
const DEFAULT_ISEASN = ISEASN.DEFAULT;
const DISABLED_ISEASN = [];

enum IVULCN {
  DEFAULT = 0,
  STRATOSPHERIC_BACKGROUND = 1,
  AGED_VOLCANIC_MODERATE = 2,
  FRESH_VOLCANIC_HIGH = 3,
  AGED_VOLCANIC_HEIGHT = 4,
  FRESH_VOLCANIC_MODERATE = 5,
  BACKGROUND_STRATOSPHERIC_MODERATE_VOLCANIC = 6,
  BACKGROUND_STRATOSPHERIC_HIGH_VOLCANIC = 7,
  FRESH_VOLCANIC_EXTREME = 8,
}

const DEFAULT_IVULCN = IVULCN.STRATOSPHERIC_BACKGROUND;
const DISABLED_IVULCN = [
  IVULCN.DEFAULT /**disabled as defaults to stratospheric background */,
];

enum ICLD {
  NO_CLOUDS_OR_RAIN = 0,
  CUMULUS_CLOUD_BASE = 1,
  ALTOSTRATUS_CLOUD_BASE = 2,
  STRATUS_CLOUD_BASE = 3,
  STRATUS_STRATO_CU_BASE = 4,
  NIMBOSTRATUS_CLOUD_BASE = 5,
  STRATUS_CLOUD_BASE_2MM_DRIZZLE = 6,
  NIMBOSTRATUS_CLOUD_BASE_5MM_LIGHT_RAIN = 7,
  NIMBOSTRATUS_CLOUD_BASE_12d5MM_MODERATE_RAIN = 8,
  CUMULUS_CLOUD_BASE_25MM_HEAVY_RAIN = 9,
  CUMULUS_CLOUD_BASE_75MM_EXTREME_RAIN = 10,
  USER_DEFINED = 11,
  STANDARD_CIRRUS = 18,
  SUB_VISUAL_CIRRUS = 19,
  NOAA_CIRRUS = 20,
}

const DISABLED_ICLD = [ICLD.USER_DEFINED];
const DEFAULT_ICLD = ICLD.NO_CLOUDS_OR_RAIN;

function enumKeys<O extends object, K extends keyof O = keyof O>(obj: O): K[] {
  return Object.keys(obj).filter((k) => Number.isNaN(+k)) as K[];
}

function setupModule(onLoaded) {
  setTimeout(() => {
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

    onLoaded();
    console.log("loaded");
    Module.setStatus("Downloading...");
    window.onerror = function () {
      Module.setStatus("Exception thrown, see JavaScript console");

      Module.setStatus = function (text) {
        if (text) Module.printErr("[post-exception status] " + text);
      };
    };
  }, 1000);
}

const LowtranDemo = () => {
  const [modul, setModul] = useState(null);
  const [model, setModel] = useState(1);

  const [height1, setHeight1] = useState(5);
  const [height2, setHeight2] = useState(10);

  const [iSeasn, setISeasn] = useState(DEFAULT_ISEASN);
  const [iHaze, setIHaze] = useState(DEFAULT_IHAZE);
  const [iVulcn, setIVulcn] = useState(DEFAULT_IVULCN);
  const [iCld, setICld] = useState(DEFAULT_ICLD);

  const [range, setRange] = useState(10);

  const { width, height } = useWindowSize();

  useEffect(() => {
    setupModule(() => {
      setModul("loaded");
    });
  }, [setModul]);

  const data = useMemo(() => {
    if (
      typeof window === "undefined" ||
      window?.["Module"] == null ||
      window?.["Module"]?.runLowtran == null
    ) {
      return;
    }

    console.log(range, height1, height2);
    if (range < height2 - height1 + 0.5) {
      setRange(Math.ceil(height2 - height1) + 0.5);
      console.log("Range");
      return;
    }

    console.log(model);
    let lowtran7 = window["Module"];
    // console.log(window["Module"]);

    console.log(iVulcn);
    var result = lowtran7.runLowtran(
      {
        model,
        itype: 2,
        iemsct: 0,
        m1: 0,
        m2: 0,
        m3: 0,
        im: 1,
        noprt: 0,
        tbound: 0,
        salb: 0,
      },
      { m4: 0, m5: 0, m6: 0, mdef: 0, ird1: 0, ird2: 0 },
      { wair1: 0, jlow: 0 },
      {
        ihaze: iHaze,
        iseasn: iSeasn,
        ivulcn: iVulcn,
        icstl: 0,
        icld: iCld,
        ivsa: 0,
        vis: 0,
        wss: 0,
        whh: 0,
        rainrt: 0,
      },
      { cthik: 0, calt: 0, cext: 0, iseed: 0 },
      { zcvsa: 0, ztvsa: 0, zinvsa: 0 },
      { ml: 0, title: "" },
      {},
      { h1: height1, h2: height2, angle: 0, range, beta: 0, re: 0, len: 0 },
      { iparm: 0, iph: 0, iday: 0, isourc: 0 },
      {
        parm1: 0,
        parm2: 0,
        parm3: 0,
        parm4: 0,
        time: 0,
        psio: 0,
        anglem: 0,
        g: 0,
      },
      { v1: 0, v2: 0, dv: 0 }
    );

    console.log("New range", range);
    // console.log(" JS side pointer: " + result[0] + " size: " + result[1]);

    let xs = [];
    let ys = [];

    for (var i = 0; i < result[1]; i++) {
      let val = lowtran7.HEAPF32[(result[0] + i * 4) / 4];

      if (i % 2 === 0) {
        xs.push(val * 1000);
      } else {
        ys.push(val);
      }
    }

    // result.delete();

    lowtran7._free(result[0]);
    return { x: xs, y: ys };
  }, [
    modul,
    model,
    height1,
    height2,
    iCld,
    range,
    iHaze,
    iVulcn,
    iSeasn,
    setRange,
  ]);

  return (
    <div style={{ width: "100%", height: "100%" }}>
      <Head>
        <script src="a.out.js"></script>
      </Head>
      <div style={{ position: "fixed", left: 0, top: 0, width: "60%" }}>
        <Plot
          data={[data]}
          layout={{
            width: width * 0.6,
            height: height * 0.8,
            title: "Lowtran7",
            xaxis: {
              title: "Wavelength (nm)",
            },
            yaxis: {
              title: "Transmission (Dimensionless)",
            },
          }}
        ></Plot>
      </div>
      <div
        style={{
          width: "35%",
          height: "100%",
          backgroundColor: "rgb(240, 240, 240)",
          position: "fixed",
          fontSize: "13px",
          padding: "2em 2em 2em 2em",
          top: 0,
          right: 0,
        }}
      >
        <Typography variant="h4">Config</Typography>
        <Divider style={{ marginBottom: "2em" }} />
        <InputLabel>Model</InputLabel>
        <Select
          defaultValue={DEFAULT_MODEL}
          onChange={(ev) => setModel(Number(ev.target.value))}
          size="small"
        >
          {enumKeys(MODEL).map((modelName) => {
            return (
              <MenuItem
                key={modelName}
                disabled={DISABLED_MODELS.includes(MODEL[modelName])}
                value={MODEL[modelName]}
              >
                {modelName}
              </MenuItem>
            );
          })}
        </Select>
        <InputLabel>Height 1 -- {height1}km</InputLabel>

        <Slider
          onChange={(ev, newHeight1) => setHeight1(Number(newHeight1))}
          defaultValue={5}
          min={0}
          max={30}
          step={0.1}
        />
        <InputLabel>Height 2 -- {height2}km</InputLabel>
        <Slider
          onChange={(ev, newHeight2) => setHeight2(Number(newHeight2))}
          defaultValue={10}
          min={0}
          max={30}
          step={0.1}
        />
        <InputLabel>Range (Direct) -- {range}km</InputLabel>
        <Slider
          onChange={(ev, newRange) => setRange(Number(newRange))}
          defaultValue={10}
          min={Math.abs(height2 - height1)}
          max={60}
        />
        <InputLabel>Haze</InputLabel>
        <Select
          defaultValue={DEFAULT_IHAZE}
          onChange={(ev) => setIHaze(Number(ev.target.value))}
          size="small"
        >
          {enumKeys(IHAZE).map((IHAZEName) => {
            return (
              <MenuItem
                key={IHAZEName}
                disabled={DISABLED_IHAZE.includes(IHAZE[IHAZEName])}
                value={IHAZE[IHAZEName]}
              >
                {IHAZEName}
              </MenuItem>
            );
          })}
        </Select>
        <InputLabel>Season</InputLabel>
        <Select
          defaultValue={DEFAULT_ISEASN}
          size="small"
          onChange={(ev) => setISeasn(Number(ev.target.value))}
        >
          {enumKeys(ISEASN).map((ISEASNName) => {
            return (
              <MenuItem
                key={ISEASNName}
                disabled={DISABLED_ISEASN.includes(ISEASN[ISEASNName])}
                value={ISEASN[ISEASNName]}
              >
                {ISEASNName}
              </MenuItem>
            );
          })}
        </Select>
        <InputLabel>Volcanic Activity</InputLabel>
        <Select
          defaultValue={DEFAULT_IVULCN}
          size="small"
          onChange={(ev) => setIVulcn(Number(ev.target.value))}
        >
          {enumKeys(IVULCN).map((IVULCNName) => {
            return (
              <MenuItem
                key={IVULCNName}
                disabled={DISABLED_IVULCN.includes(IVULCN[IVULCNName])}
                value={IVULCN[IVULCNName]}
              >
                {IVULCNName}
              </MenuItem>
            );
          })}
        </Select>
        <InputLabel>Cloud Activity</InputLabel>
        <Select
          defaultValue={DEFAULT_ICLD}
          size="small"
          onChange={(ev) => setICld(Number(ev.target.value))}
        >
          {enumKeys(ICLD).map((ICLDName) => {
            return (
              <MenuItem
                key={ICLDName}
                value={ICLD[ICLDName]}
                disabled={DISABLED_ICLD.includes(ICLD[ICLDName])}
              >
                {ICLDName}
              </MenuItem>
            );
          })}
        </Select>
      </div>
    </div>
  );
};

export default LowtranDemo;
