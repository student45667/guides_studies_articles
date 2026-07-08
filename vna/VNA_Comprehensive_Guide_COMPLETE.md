# Comprehensive Guide: VNA Measurement Methodologies for Amplifiers and TIAs

**A complete reference covering passive fixture measurements, active amplifier characterization, high-impedance TIA inputs, bias tees, conical coils, and practical examples.**

---

## Table of Contents

1. [Introduction & User Questions](#introduction--user-questions)
2. [Fundamental Concepts](#fundamental-concepts)
3. [dBm to Watts & Voltage Conversion](#dbm-to-watts--voltage-conversion)
4. [VNA Measurement for Active Amplifiers](#vna-measurement-for-active-amplifiers)
5. [Bias Tees & Conical Coils](#bias-tees--conical-coils)
6. [Output Attenuators & VNA Protection](#output-attenuators--vna-protection)
7. [TIA Measurements with VNA](#tia-measurements-with-vna)
8. [Practical Examples & Literature](#practical-examples--literature)
9. [Source Links & References](#source-links--references)

---

## Introduction & User Questions

### User's Background & Goals

**User Profile:**
- Hardware/semiconductor engineer with ~15 years experience (mixed-signal ASIC test, ATE development, SI/PI, embedded hardware)
- Recently accepted role at Ciena
- Actively pursuing AI freelance consulting ($100–150/hr, $5–15K/project)
- Focus areas: wafer data analysis, test pattern verification, embedded code generation
- Runs renovation company (A.C.H. Homes) on the side
- Location: Ottawa (Kanata), Ontario, Canada

### Initial Questions Posed

**Q1: "I'm an RF expert helping understand VNA measurement methodologies. I'm familiar with passive fixtures (single-ended, differential). I want to understand how to measure input/output impedance and gain of an amplifier—methodology, setup, de-embedding, calibration, and how to get S-parameters."**

→ **Answer**: See Section 4 (VNA Measurement for Active Amplifiers) for complete setup, calibration strategy, and S-parameter extraction.

**Q2: "Do I need to place attenuators on the output to not harm the VNA or to stay in the measurement range?"**

→ **Answer**: See Section 6. Yes, primarily for **VNA protection** (receivers typically rated +20 to +30 dBm max). 6–10 dB attenuators are standard for high-gain amplifiers.

**Q3: "Search through the internet for data about amplifier measurements with VNA, show examples of bias tees as well, possibly conical coils."**

→ **Answer**: See Section 5 and 9. Comprehensive commercial products, specifications, and application notes from Coilcraft, Analog Devices, and manufacturers included.

**Q4: "Search methodologies of feeding signal to TIA from VNA (it is high impedance input btw)."**

→ **Answer**: See Section 7. Three methodologies covered: direct S→Z conversion, matching networks, and transmission line matching.

---

## Fundamental Concepts

### Passive vs. Active Measurements

| Aspect | Passive Fixture | Active Amplifier |
|--------|-----------------|------------------|
| **Power supply** | None | Required (VCC, VGS/IDS) |
| **Bias point** | N/A | Critical (defines gain, impedance) |
| **S-parameters** | Frequency-independent (ideally) | Bias-dependent |
| **Stability** | Always stable | Risk of oscillation |
| **Measurement concern** | Path loss, discontinuities | Gain, impedance transformation, oscillation |

### Key Terminology

- **S-parameters**: Scattering parameters; voltage ratios in a 50 Ω system
- **Z-parameters**: Impedance matrix; includes transimpedance (V/I)
- **Return loss**: dB magnitude of reflected signal; RL = −20 log₁₀(|Γ|)
- **Insertion loss**: dB magnitude of transmitted signal through passive network
- **Bias tee**: High-pass network for RF, low-pass for DC; allows simultaneous AC/DC injection
- **Transimpedance (TIA)**: Amplifier topology converting input current to output voltage
- **De-embedding**: Mathematically removing fixture parasitics to move reference plane to DUT terminals

---

## dBm to Watts & Voltage Conversion

### Conversion Formulas

**dBm to Watts:**
$$P_{watts} = \frac{10^{dBm/10}}{1000}$$

**dBm to Voltage (50 Ω system):**
$$V_{peak} = \sqrt{P_{watts} \times 50}$$

### Reference Table: 10–40 dBm

| **dBm** | **Watts** | **mW** | **Peak Voltage (V)** | **Peak Voltage (mV)** |
|---------|-----------|--------|----------------------|----------------------|
| 10 | 0.01 W | 10 mW | 0.707 V | 707 mV |
| 20 | 0.1 W | 100 mW | 2.236 V | 2,236 mV |
| 30 | **1 W** | 1,000 mW | **7.071 V** | 7,071 mV |
| 40 | 10 W | 10,000 mW | 22.361 V | 22,361 mV |

### Key Insight: Decibel Doubling Rule

- **Every +10 dB = 10× power increase**
  - 10 → 20 dBm: 10 mW → 100 mW
  - 20 → 30 dBm: 100 mW → 1 W (your reference)
  - 30 → 40 dBm: 1 W → 10 W (danger zone)

- **Every +3 dB ≈ 1.414× voltage increase** (√2)

### VNA Safety Context

| Power | Status | Recommendation |
|-------|--------|-----------------|
| +10 to +20 dBm | Safe | Typical small-signal drive |
| +20 to +25 dBm | Marginal | Add attenuator if unsure |
| +25 to +30 dBm | At limit | Use 6–10 dB attenuator |
| >+30 dBm | Exceeds rating | **Mandatory 10+ dB attenuator** (damage risk) |

---

## VNA Measurement for Active Amplifiers

### System Architecture

```
                    ┌─────────────────────────────────────┐
                    │         AMPLIFIER UNDER TEST        │
                    │                                     │
Port 1 ────────────→│  [Bias Tee 1]  Amp  [Bias Tee 2]  │────────────→ Port 2
(Source, 50Ω)      │        ↓                     ↓      │  (Receiver, 50Ω)
                    │       VCC                   VCC     │
                    │                                     │
                    │  S11 (input)   S21 (gain)  S22 (out)│
                    │  S12 (isolation)                    │
                    └─────────────────────────────────────┘
```

### Calibration Strategy

#### Option 1: SOL at VNA Ports (Standard, Most Common)

```
Calibration plane at VNA connectors (before bias tees)
  VNA ──[Cal: Short/Open/Load]
              ↓
         Removes cable/connector loss
```

**Advantages:**
- Simple; uses standard 50 Ω calibration kit
- Bias tees are passive; included in measurement
- Fast calibration

**Disadvantages:**
- Bias tee parasitics remain in measurement
- If tees are lossy, dynamic range reduced

#### Option 2: TRL at Bias Tee Plane (Advanced, Recommended for Precision)

```
Calibration plane at bias tee input/output
  VNA ──[Bias Tee]──[Cal: Thru/Reflect/Line]
       ↓
  Removes bias tee insertion loss & phase
  Absorbs fixture response completely
```

**Advantages:**
- De-embeds bias tee automatically
- Impedance-agnostic (works even if not 50 Ω)
- Best accuracy for active devices

**Disadvantages:**
- Requires building/calibrating TRL standards
- Thru: fixture with no DUT
- Reflect: open or short at DUT plane
- Line: known delay transmission line

### Measurement Procedure: Step-by-Step

1. **Calibrate VNA**
   - Choose SOL (quick) or TRL (better)
   - Note: Bias tees present → include in calibration

2. **Apply DC Bias**
   - Set VCC via external supply or integrated bias tee
   - Set gate/collector bias to desired operating point
   - Monitor with **inline DMM** (critical for repeatability)
   - Example: VCC = +5 V, VGS = −1 V, ICC = 50 mA

3. **Verify Stability**
   - Set RF input power to **−10 dBm** (small-signal regime)
   - Measure with spectrum analyzer + sniffer antenna
   - Look for **smooth phase rotation** and stable gain
   - Any sudden oscillation → reduce power or adjust bias

4. **Sweep Frequency**
   - Typical: 100 MHz to 40–50 GHz (VNA dependent)
   - Can extend to 110+ GHz for mmWave VNA
   - Resolution trade-off: fewer points = faster sweep, less accurate

5. **Capture All S-Parameters**
   - S₁₁: input reflection (input impedance)
   - S₁₂: reverse isolation (leakage)
   - S₂₁: forward transmission (gain)
   - S₂₂: output reflection (output impedance)

6. **Export Touchstone Format (.s2p)**
   ```
   ! Amplifier S-parameters
   ! VCC=5V, VGS=-1V, Freq=100M-50G, Input Power=-10dBm
   # Hz S MA R 50
   1.0e8  S11_mag  S11_phase  S21_mag  S21_phase  ...
   ```

### De-embedding: Moving Reference Planes

#### Port Extension Method (Simplest)

Removes matched transmission line effect from measurement to DUT:

```
Measurement plane ──[Delay τ]──→ DUT plane
  (at fixture)        (PCB trace)
```

**Formula:**
$$\tau = \frac{L}{v_p}$$

where:
- L = physical length (e.g., 25 mm)
- v_p = phase velocity (~0.6c on FR4 PCB = 0.18 m/ns)

**In VNA**: Use "port extension" or "delay correction" menu; specify delay in seconds or length in mm.

**Limitations**: Assumes lossless, non-dispersive transmission line. Real PCB has loss & dispersion → residual error remains.

#### Fixture De-embedding (Advanced)

Numerically remove known test fixture from measurement:

```
Step 1: Measure fixture alone (no DUT)     → S_fixture
Step 2: Measure fixture + DUT             → S_total
Step 3: Remove cascade: S_DUT = S_total ÷ S_fixture (ABCD algebra)
```

**Tools:**
- Keysight ADS, Ansoft HFSS
- `scikit-rf` Python library
- Most modern VNA firmware includes this

**Cascaded S-parameter removal (ABCD matrix method):**
1. Convert S-parameters to ABCD (chain) parameters
2. Divide (or multiply inverse) to isolate DUT
3. Convert back to S-parameters

### Impedance Extraction from S-Parameters

**Input impedance:**
$$Z_{in} = Z_0 \frac{1 + S_{11}}{1 - S_{11}} = 50 \frac{1 + S_{11}}{1 - S_{11}}$$

**Output impedance:**
$$Z_{out} = Z_0 \frac{1 + S_{22}}{1 - S_{22}} = 50 \frac{1 + S_{22}}{1 - S_{22}}$$

**Reflection coefficient:**
$$\Gamma = S_{11} \text{ (or } S_{22} \text{)}$$

**Return loss (dB):**
$$RL = -20 \log_{10}(|\Gamma|)$$

**VSWR:**
$$\text{VSWR} = \frac{1 + |\Gamma|}{1 - |\Gamma|}$$

### Gain & Stability

**Forward transmission (gain):**
$$G_f = 20 \log_{10}(|S_{21}|) \text{ dB}$$

**Reverse isolation:**
$$G_r = 20 \log_{10}(|S_{12}|) \text{ dB}$$

**Stability Factor (K-factor) – unconditional stability check:**
$$K = \frac{1 + |\Delta|^2 - |S_{11}|^2 - |S_{22}|^2}{2|S_{12}S_{21}|}$$

where $\Delta = S_{11}S_{22} - S_{12}S_{21}$ (determinant)

- **K > 1**: Unconditionally stable (safe at any load/source impedance)
- **K < 1**: Potentially unstable (risk of oscillation)

**Mu stability (alternative):**
$$\mu = \frac{1 - |S_{11}|^2}{|S_{22} - \Delta^* S_{11}| + |S_{12}S_{21}|}$$

- **μ > 1**: Stable

---

## Bias Tees & Conical Coils

### What is a Bias Tee?

A **passive network** allowing simultaneous RF (AC) and DC injection:

```
        │ VCC (DC)
        │
        R (limiting resistor, 10-100Ω)
        │
        ├──────┬──── RF_in/RF_out
        │      │
       [L]  [C_block]
       (RF choke)  (AC coupling)
        │      │
        └──┬───┘
           │
          GND
```

**Function:**
- **Capacitor**: Blocks DC from RF path; passes AC
- **Inductor**: Blocks RF from DC supply; passes DC

**Key challenge**: Inductor must have **no self-resonance in RF band**, else creates notch in response.

### Conical Coil Design (Broadband Solution)

A **conical spiral** (tapered diameter) avoids sharp resonances:

```
       Tip (small diameter)
          ▲
         ╱│╲
        ╱ │ ╲  ← High freq supported by small turns
       ╱  │  ╲
      ╱   │   ╲
     ╱    │    ╲
    ╱     │     ╲
   Base (large diameter)
   ↑
   Low freq supported by large turns
```

**Why it works:**
- High frequencies supported by **small-diameter tip** (low inductance = high impedance at high freq)
- Low frequencies supported by **large-diameter base** (high inductance)
- **Distributed capacitances** (turn-to-turn, turn-to-ground) are also distributed → no single resonance peak
- Result: **Flat impedance response** 10 MHz–40 GHz

### Commercial Conical Products

#### Coilcraft 4310LC Series (DC–6 GHz)

**Specifications:**
- **Frequency range**: DC–6 GHz
- **Inductance**: 3.3 µH to 220 µH (measured at 100 kHz)
- **DCR**: 0.04–0.3 Ω (depends on inductance)
- **Current rating**: 0.6–10 A RMS
- **Insertion loss**: <0.5 dB @ 1 GHz, ~2–3 dB @ 6 GHz
- **Cost**: ~$3 per unit

**Use cases:**
- TV antenna biasing (500 mA DC, 20 MHz–2 GHz blocking)
- Low-to-mid frequency RF circuits

**Datasheet**: https://www.coilcraft.com/en-us/products/rf/conical-broadband/0-6-ghz/4310lc/

#### Coilcraft BCR Series (DC–40 GHz) – Ultra-Wideband

**Specifications:**
- **Frequency range**: 10 MHz–40 GHz (ultra-wideband)
- **Inductance**: 1.6 nH to 820 nH (measured at 10 MHz)
- **DCR**: 0.01–0.1 Ω
- **Current rating**: 0.35–0.6 A RMS
- **Insertion loss**: <0.5 dB @ 100 MHz, <1.0 dB @ 10 GHz, <2 dB @ 35 GHz
- **Cost**: ~$8–15 per unit
- **Structure**: Multi-stage conical winding on ferrite core; distributed impedance stages
- **Typical measurement**: Tested in bias tee configuration with HP 8722ES VNA

**Use cases:**
- Pin diode biasing (200 mA DC, 100 MHz–30 GHz)
- Amplifier gate/collector biasing (high-frequency)
- mmWave bias injection

**Datasheet**: https://www.coilcraft.com/en-us/products/rf/conical-broadband/0-40-ghz/bcr/

#### Analog Devices AN-2061: Discrete Component Bias Tee Design

**Alternative**: Build wideband bias tee from 0402/0805 SMD components.

**Circuit:**
- **DC block**: 1–100 nF capacitor (C0G or X7R dielectric, high voltage rating)
- **RF choke**: Multiple inductors (2–10 nH to 10 µH) in series OR ferrite bead
- **De-Q resistor**: 100 Ω in parallel with bypass cap (optional; improves flatness)
- **Bypass capacitor**: 10–100 nF to ground

**Advantages:** Lower cost (~$0.50), smaller PCB footprint
**Disadvantages:** Limited bandwidth (typically DC–6 GHz), resonance management required

**Reference**: https://www.analog.com/en/resources/app-notes/an-2061.html

---

## Output Attenuators & VNA Protection

### Why Output Attenuators Are Needed

**VNA receiver maximum input power**: +20 to +30 dBm (device-dependent)
- Keysight N5230C: +30 dBm
- Rohde & Schwarz ZNA: +25 dBm

**Exceeding this → burns out low-noise input stage (permanent damage)**

### Calculation Example

**Scenario:**
- Amplifier gain: +30 dB
- VNA Port 1 output: +5 dBm
- **Amplifier output**: 5 + 30 = **+35 dBm** ✗ (exceeds +30 dBm limit)
- **Solution**: Add 10 dB pad → −5 dBm to VNA Port 2 ✓ (safe)

### Selecting Attenuator Size

| Amp Gain | Input Power | Amp Output | Attenuator | Final to VNA | Status |
|----------|-------------|------------|------------|--------------|--------|
| +15 dB | −5 dBm | +10 dBm | None | +10 dBm | ✓ Safe |
| +25 dB | +0 dBm | +25 dBm | 6 dB | +19 dBm | ✓ Safe |
| +30 dB | +5 dBm | +35 dBm | 10 dB | +25 dBm | ✓ Safe |
| +40 dB | +0 dBm | +40 dBm | 20 dB | +20 dBm | ✓ Safe |

**Rule of thumb**: Keep VNA input **≤ +20 dBm** for margin of safety.

### De-embedding the Attenuator

The attenuator is now **part of your measured S-parameters**:

```
Measured: S_amp_cascade = S_amp ⊕ S_attenuator
                          (cascade)
```

**Option A: Report the cascade** (system-level specs)
- "S-parameters measured with 10 dB output pad"
- Useful for design that includes the pad

**Option B: De-embed the attenuator** (amp-only specs)
1. Measure attenuator alone (S_pad)
2. Use cascade removal (ABCD matrix inversion)
3. Extract amp-only S-parameters

**Python example (scikit-rf):**
```python
import skrf as rf

cascade = rf.Network('amp_with_pad.s2p')
pad = rf.Network('pad_10db.s2p')  # or use vendor spec

amp_only = cascade.cascade(pad.inv())  # Remove pad from cascade
amp_only.write_touchstone('amp_only.s2p')
```

**Why bother?** Attenuator is **linear, passive, well-characterized**; removing it is straightforward and useful for IC design/simulation models.

### Impedance Impact

Standard coaxial attenuators:
- **Type**: 50 Ω fixed pads (SMA or N-type connectors)
- **Insertion loss**: Nominal (e.g., 6 dB pad = 6 dB ± 0.2 dB)
- **Impedance**: 50 Ω in/out (matched)
- **Frequency range**: DC–50 GHz (depends on grade)

**No de-embedding needed for impedance**—attenuator is already 50 Ω.

---

## TIA Measurements with VNA

### Challenge: High-Impedance Input

**Transimpedance Amplifier (TIA):**
- **Input node**: Virtual ground (inverting input of feedback op-amp)
- **Input impedance**: 25–100 Ω (set by feedback resistor R_f and op-amp input stage)
- **Example**: 5 kΩ feedback resistor → ~5 kΩ / (1 + open-loop gain) ≈ 50–100 Ω input
- **BUT**: When measured **without photodiode**, input appears capacitive/complex → impedance not simply 50 Ω

**VNA is 50 Ω system** → potential mismatch if TIA input impedance deviates.

### Three Measurement Methodologies

#### Methodology 1: Direct S-Parameter to Z-Parameter Conversion ✓ Most Common

**Setup:**
```
VNA Port 1 ──[DC block cap]──→ TIA input
                                ↓
                              [Bias via bias tee]
                                ↓
VNA Port 2 ←─────────────────── TIA output
```

**Procedure:**

1. **Calibrate VNA** at 50 Ω (SOL)
2. **Apply DC bias** (e.g., +5 V supply via bias tee; typically 1 mA bias current)
3. **Measure S-parameters**:
   - Input power: −30 to −40 dBm (small-signal linear region)
   - Frequency: 100 kHz–10 GHz typical (can extend to 50 GHz)
   - Capture all S₁₁, S₁₂, S₂₁, S₂₂

4. **Convert S → Z using matrix transformation:**

$$[Z] = Z_0 \begin{bmatrix} \frac{(1+S_{11})(1-S_{22}) + S_{12}S_{21}}{(1-S_{11})(1-S_{22}) - S_{12}S_{21}} & \frac{2S_{12}}{(1-S_{11})(1-S_{22}) - S_{12}S_{21}} \\ \frac{2S_{21}}{(1-S_{11})(1-S_{22}) - S_{12}S_{21}} & \frac{(1-S_{11})(1+S_{22}) + S_{12}S_{21}}{(1-S_{11})(1-S_{22}) - S_{12}S_{21}} \end{bmatrix}$$

5. **Extract Z₂₁ (transimpedance gain):**

$$Z_{21} = Z_0 \frac{2S_{21}}{(1-S_{11})(1-S_{22}) - S_{12}S_{21}}$$

6. **Convert to dBΩ:**

$$Z_{21\,dB} = 20 \log_{10}(|Z_{21}|)$$

**Result**: Transimpedance gain in Ohms; −3 dB bandwidth; gain vs. frequency plot.

**Tools:**
- VNA built-in S→Z menu (most modern instruments)
- Python `scikit-rf` library:
  ```python
  import skrf as rf
  ntwk = rf.Network('tia.s2p')
  Z = ntwk.z  # Z-parameters at each frequency
  Z21 = Z[:, 1, 0]  # Extract Z21
  Z21_dB = 20 * np.log10(np.abs(Z21))
  ```

**Advantages:**
- Simple; no extra components
- Direct to S-parameter measurement
- Accurate

**Disadvantages:**
- Requires matrix math or VNA firmware
- If input impedance very high (>1 MΩ), S11 weak → noisy measurement

---

#### Methodology 2: Impedance Matching Network (Transformer + Inductor)

**For very high source impedance** (e.g., discrete high-impedance photodiode, >1 MΩ):

**Setup:**
```
Photodiode/Signal ──[L: 50-200 nH]──[Transformer 16:1]──→ TIA input (50Ω)
  (high Z, µA)      (series)           (impedance ratio)   (low Z)
```

**Why it works:**
- Photodiode is a **high-impedance current source** with large parallel capacitance (~100 pF)
- Transformer impedance ratio steps up the 50 Ω TIA input impedance to match photodiode (e.g., 16:1 ratio → 800 Ω)
- Series inductor de-resonates the transformer; ensures flat response across bandwidth

**Component Selection:**

**Transformer:**
- **4:1 ratio**: 200 Ω source → 50 Ω load (moderate Z match)
- **9:1 ratio**: 450 Ω source → 50 Ω load
- **16:1 ratio**: 800 Ω source → 50 Ω load (high source Z)

**Series inductor:**
- **Value**: 20–1000 nH (typically 50–200 nH for broadband)
- **Purpose**: Resonates with transformer parasitic capacitance
- **Result**: Flat response 10 MHz–550 MHz (vs. transformer peaking)

**Real example (broadband optical receiver patent):**
- Transformer alone: Considerable gain at 10 MHz, reduced at 550 MHz
- Transformer + 50 nH series inductor: Flat response across entire band

**Source**: US Patent 5179461 (Broadband optical receiver with passive tuning network)
https://image-ppubs.uspto.gov/dirsearch-public/print/downloadPdf/5179461

**Advantages:**
- Extends measurement range to very high source impedances
- Improves power transfer (matches impedances)

**Disadvantages:**
- Adds insertion loss (~1–2 dB)
- Transformer insertion loss measured in bias tee configuration varies with frequency
- Component-dependent performance (quality of transformer)

---

#### Methodology 3: Transmission Line Impedance Matching (PCB-Based)

**For integrated receiver modules** (remote photodiode + TIA on same chip/PCB):

**Principle:**
- PCB **transmission lines** between photodiode and TIA are designed with controlled impedance
- Impedance matched to within ±50% of TIA input impedance
- Minimizes ringing and reflections at high data rates

**Example (from optical receiver module patents):**

```
Photodiode (remote)  ──[PCB transmission line Z2]──→  TIA input (Z1)
                        (50 Ω trace impedance)      (100 Ω impedance)
```

**Impedance matching condition:**
$$0.5 \times Z_1 \leq Z_2 \leq 1.5 \times Z_1$$

e.g., TIA Z1 = 100 Ω → trace impedance 50–150 Ω (within ±50%)

**Result:**
- Minimal reflections (return loss >10 dB)
- Supports 5–10 Gbps data rates
- PCB fabrication with controlled dielectric (FR4 or ceramic)

**Advantages:**
- Integrated (no discrete components)
- Flat broadband response
- Scalable to integrated photonics

**Disadvantages:**
- Requires controlled PCB impedance (adds cost/complexity)
- Only applicable to integrated designs

**Source**: US Patents 9354411, 9148960 (Receiver optical assemblies with remote photodiode)
https://image-ppubs.uspto.gov/dirsearch-public/print/downloadPdf/9354411

---

### Critical Factor: Photodiode Capacitance

**TIA bandwidth is dominated by the input RC pole:**

$$f_{-3dB} = \frac{g_m}{2\pi(C_{PD} + C_{opamp})}$$

where:
- $g_m$ = transconductance of input stage
- $C_{PD}$ = photodiode capacitance (typically 0.5–1 pF for silicon PIN)
- $C_{opamp}$ = op-amp input parasitic capacitance (~450 fF)
- **Total**: 0.6–1.5 pF typical

**Measurement implication**: When measuring a TIA **without photodiode attached**, the measured bandwidth is **artificially high** because C_in is lower. Once you attach the real photodiode, bandwidth collapses.

**Workaround**: 
1. Simulate photodiode by adding 10–100 pF capacitor to TIA input during VNA test
2. Measure with capacitor in place
3. Real system bandwidth will match

**Real example (TI E2E Forum):**
- **Device**: OPA818 + 5 kΩ feedback
- **Problem**: Measured gain was lower than expected (74 dBΩ)
- **Root cause**: Unmeasured input capacitance (op-amp + PCB parasitic); TIA was loading itself
- **Solution**: Added 33 pF capacitor in parallel with feedback resistor to simulate photodiode; gain then matched predictions

**Source**: https://e2e.ti.com/support/amplifiers-group/amplifiers/f/amplifiers-forum/1064582/opa818-testing-tia-with-vna (TI E2E Support Forum)

---

### S-Parameter to Transimpedance Conversion

**Relationship: TIA is fundamentally a transimpedance device**

Input: current I_in (from photodiode)
Output: voltage V_out

$$Z_T = \frac{V_{out}}{I_{in}} = Z_{21} \text{ (Z-parameter)}$$

**For a 2-port TIA measured with VNA (S-parameters):**

$$Z_{21} = Z_0 \frac{2S_{21}}{(1-S_{11})(1-S_{22}) - S_{12}S_{21}}$$

**where Z₀ = 50 Ω**

**In dBΩ:**
$$Z_{21\,dB} = 20 \log_{10}(|Z_{21}|)$$

**Typical values for optical TIAs:**
| Feedback R_f | Z_T Magnitude | Z_T (dBΩ) |
|--------------|---------------|-----------|
| 1 kΩ | 1000 Ω | 60 dBΩ |
| 5 kΩ | 5000 Ω | 74 dBΩ |
| 10 kΩ | 10000 Ω | 80 dBΩ |
| 100 kΩ | 100000 Ω | 100 dBΩ |

---

### Practical Example: 10 Gbps Optical TIA

**Reference:** Microwave Journal, "Fast Calculation of Transimpedance Gain and Equivalent Input Noise Current Density for High-speed Optical Preamplifier Design" (2012)

**Device specs:**
- **Feedback resistance**: 5 kΩ (variable)
- **Frequency range**: 100 kHz–10 GHz (VNA measurement)
- **Input power**: −45 dBm (low, to avoid saturation)

**Results:**
- **Peak Z₂₁**: ~80 dBΩ (5000 Ω), measured from S21 S-parameters
- **−3 dB bandwidth**: Strongly dependent on photodiode capacitance:
  - C_PD = 0.1 pF → BW ≈ 14 GHz
  - C_PD = 0.6 pF → BW ≈ 8 GHz (10 Gbps operation limit)
  - C_PD > 1 pF → BW < 5 GHz (unsuitable for 10 Gbps)

**Key lesson**: The **photodiode capacitance is the dominant factor** in TIA bandwidth, not the op-amp bandwidth.

**Source:** https://www.microwavejournal.com/articles/11113-fast-calculation-of-transimpedance-gain-and-equivalent-input-noise-current-density-for-high-speed-optical-preamplifier-design

---

### Practical Example: 133 GHz InP DHBT TIA

**Reference:** UCL Discovery, "Transimpedance Amplifiers with 133 GHz bandwidth on 130nm InP DHBT" (2018)

**Device specs:**
- **Process**: 130 nm InP DHBT (ft/fmax = 520 GHz / 1.15 THz)
- **Topologies**: Common-base (CB) and common-emitter (CE) with shunt-shunt feedback
- **Power consumption**: 32.3 mW (CB), 25.5 mW (CE)

**Measurement setup:**
- **VNA**: Cascade Infinity 67 GHz GSG probes
- **Input power**: −30 dBm (to avoid compression at mmWave)
- **Frequency**: On-wafer TRL calibration to 67 GHz; measurement to 133 GHz via extrapolation
- **De-embedding**: Pad parasitics removed using open/short reference structures

**Results:**
- **Input impedance Z₁₁**: 25 Ω (CB, well-matched), 35 Ω (CE)
- **Transimpedance gain Z₂₁**: 42 dBΩ (both topologies) with peaking on CB
- **Bandwidth**: 133 GHz (flat to this frequency)
- **Data rate tested**: Eye diagrams up to 64 Gbps
- **Input noise**: 30.2 pA/√Hz (CB), 13.9 pA/√Hz (CE)

**Significance**: Highest bandwidth TIA reported at the time; demonstrates on-wafer mmWave measurement.

**Source:** https://discovery.ucl.ac.uk/id/eprint/10087499/1/Transimpedance%20Amplifiers%20with%20133%20GHz%20bandwidth%20on%20130nm%20InP%20DHBT%20Final.pdf

---

## Practical Examples & Literature

### Complete VNA Amplifier Measurement Flow

**Given**: MMIC amplifier with expected 20 dB gain, 8–12 GHz bandwidth

**Step 1: Prepare test fixture**
```
VNA Port 1 ──[50Ω cable]──[Bias Tee 1: Coilcraft 4310LC]──→ Amp input
                                 ↓
                                +5V supply

Amp output ──[50Ω cable]──[Bias Tee 2: Coilcraft 4310LC]──[6dB Attenuator]──→ VNA Port 2
                                ↓
                               +5V return (common GND)
```

**Step 2: Calibrate**
- VNA: SOL calibration at ports (50 Ω)
- Frequency: 1 GHz–20 GHz
- Power: −10 dBm

**Step 3: Measure**
- VCC = +5 V (via bias tee)
- Input power: 0 dBm (or −10 dBm if stability concern)
- Capture S11, S12, S21, S22

**Step 4: Analyze**
```python
import skrf as rf
import numpy as np
import matplotlib.pyplot as plt

ntwk = rf.Network('amp_measured.s2p')

# Extract impedance
Z11 = ntwk.z[:, 0, 0]  # Input impedance
Z22 = ntwk.z[:, 1, 1]  # Output impedance
Z21 = ntwk.z[:, 1, 0]  # Forward transimpedance (gain per 1A input)

# For voltage gain in dB
S21 = ntwk.s[:, 1, 0]
gain_dB = 20 * np.log10(np.abs(S21))

# K-factor stability
S11 = ntwk.s[:, 0, 0]
S22 = ntwk.s[:, 1, 1]
S12 = ntwk.s[:, 0, 1]
Delta = S11 * S22 - S12 * S21
K = (1 + np.abs(Delta)**2 - np.abs(S11)**2 - np.abs(S22)**2) / (2 * np.abs(S12 * S21))

# Plot results
fig, axes = plt.subplots(3, 1, figsize=(10, 10))

axes[0].plot(ntwk.frequency.f_ghz, gain_dB)
axes[0].set_ylabel('Gain (dB)')
axes[0].set_title('Forward Gain (S21)')
axes[0].grid()

axes[1].plot(ntwk.frequency.f_ghz, np.abs(Z11), label='Z11')
axes[1].plot(ntwk.frequency.f_ghz, np.abs(Z22), label='Z22')
axes[1].set_ylabel('Impedance (Ω)')
axes[1].set_title('Input/Output Impedance')
axes[1].legend()
axes[1].grid()

axes[2].plot(ntwk.frequency.f_ghz, K)
axes[2].axhline(y=1, color='r', linestyle='--', label='K=1 (stability limit)')
axes[2].set_ylabel('K-factor')
axes[2].set_xlabel('Frequency (GHz)')
axes[2].set_title('Stability Factor')
axes[2].legend()
axes[2].grid()

plt.tight_layout()
plt.savefig('amp_analysis.png', dpi=150)
plt.show()
```

**Output**:
- Gain vs. frequency (should be flat ~20 dB in 8–12 GHz band)
- Input/output impedance (should track ~50 Ω if matched design)
- K-factor > 1 across band (if K < 1, unstable)

---

### Bias Tee Design Example: Analog Devices AN-2061

**Application**: Wideband drain bias for GaAs pHEMT, DC–28 GHz

**Circuit:**
```
        Vcc (DC supply)
           │
          [R_limit: 10-100Ω]
           │
      ┌────┴─────┐
      │           │
    [L1]        [C_bypass]
   (choke)      (10-100nF)
      │           │
      └────┬───┬──┘
           │   │
          GND [C_block]
             (1-100nF)
               │
         ←─────┴────────→ RF in/out
```

**Component selection** (for DC–28 GHz):
- **L1**: Coilcraft BCR-822J (820 nH, ultra-wideband)
- **C_block**: 100 nF, C0G (blocks DC, passes AC)
- **C_bypass**: 10 nF, low-ESR (on-die bypass)
- **De-Q resistor**: 100 Ω in series with C_bypass (optional; improves flatness)

**Result**: Flat insertion loss DC–28 GHz, supports 1 A+ bias current, protects DC supply from RF coupling.

**Advantage over conical choke**: Much cheaper (~$0.50/component vs. $8 for BCR), smaller footprint, discretely tunable.

**Source**: https://www.analog.com/en/resources/app-notes/an-2061.html

---

## Source Links & References

### Bias Tee & Conical Coil Resources

1. **Coilcraft 4310LC Series** (DC–6 GHz, broadband chokes)
   - Product page: https://www.coilcraft.com/en-us/products/rf/conical-broadband/0-6-ghz/4310lc/
   - Application note: https://www.coilcraft.com/en-us/resources/application-notes/broadband-chokes-for-bias-tee-applications/

2. **Coilcraft BCR Series** (DC–40 GHz, ultra-wideband)
   - Product page: https://www.coilcraft.com/en-us/products/rf/conical-broadband/0-40-ghz/bcr/
   - Technical note on conical inductors: https://www.coilcraft.com/en-us/edu/series/what-is-a-conical-inductor/

3. **Analog Devices AN-2061** (Wideband Bias Tee Design Using 0402 SMD Components)
   - https://www.analog.com/en/resources/app-notes/an-2061.html

4. **EDN: "A Look at Conical Inductors"** (Design principles)
   - https://www.edn.com/a-look-at-conical-inductors/

5. **In Compliance Magazine: "A Bias Tee for Broadband Measurement of Power Electronic Components"**
   - https://incompliancemag.com/a-bias-tee-for-broadband-measurement-of-power-electronic-components/

### TIA Measurement Resources

6. **Microwave Journal: "Fast Calculation of Transimpedance Gain and Equivalent Input Noise Current Density"** (2012)
   - Detailed S→Z conversion formulas for optical TIAs
   - https://www.microwavejournal.com/articles/11113-fast-calculation-of-transimpedance-gain-and-equivalent-input-noise-current-density-for-high-speed-optical-preamplifier-design

7. **UCL Discovery: "Transimpedance Amplifiers with 133 GHz bandwidth on 130nm InP DHBT"** (2018)
   - High-frequency on-wafer measurement example
   - https://discovery.ucl.ac.uk/id/eprint/10087499/1/Transimpedance%20Amplifiers%20with%20133%20GHz%20bandwidth%20on%20130nm%20InP%20DHBT%20Final.pdf

8. **TI E2E Forum: "OPA818: Testing TIA with VNA"** (2021)
   - Practical troubleshooting; photodiode capacitance impact
   - https://e2e.ti.com/support/amplifiers-group/amplifiers/f/amplifiers-forum/1064582/opa818-testing-tia-with-vna

9. **RF Essentials: "How Do I Select a Bias Tee for Injecting DC Power onto an RF Line?"**
   - Design equations and component selection
   - https://rfessentials.com/rf-knowledge-base/how-do-i-select-a-bias-tee-for-injecting-dc-power-onto-an-rf-line-without-affect/

### Patents (Optical Receiver Impedance Matching & TIA Design)

10. **US Patent 5179461: "Broadband Optical Receiver with Passive Tuning Network"**
    - Transformer + series inductor impedance matching for high-impedance photodiode
    - https://image-ppubs.julius.com/dirsearch-public/print/downloadPdf/5179461

11. **US Patent 9354411: "Receiver Optical Assemblies (ROAs) Having Photo-Detector Remotely Located from Transimpedance Amplifier"**
    - PCB transmission line impedance matching; remote photodiode architecture
    - https://image-ppubs.julius.com/dirsearch-public/print/downloadPdf/9354411

12. **US Patent 9148960: "Receiver Optical Assemblies with Impedance-Matched Transmission Lines"**
    - Detailed analysis of TIA input impedance optimization for 5–10 Gbps
    - https://image-ppubs.julius.com/dirsearch-public/print/downloadPdf/9148960

### VNA & De-embedding Resources

13. **Anritsu Application Note 11410-01168A: "On-Wafer Biasing Using Anritsu Kelvin Bias Tee"**
    - On-wafer TIA biasing and de-embedding strategies for mmWave
    - https://dl.cdn-anritsu.com/en-us/test-measurement/files/Application-Notes/Application-Note/11410-01168A.pdf

14. **Keysight/HP VNA Documentation**
    - Port extension and de-embedding menus in modern VNAs
    - Check your instrument user manual

### Tools & Software

15. **scikit-rf Python Library** (S/Z-parameter conversion)
    - https://scikit-rf.readthedocs.io/
    - Provides Network class with automatic S→Z, S→Y conversion

16. **Coilcraft Online Calculators**
    - Bias tee design aid: https://www.coilcraft.com/en-us/designers/

---

## Appendix: Quick Reference Tables

### Bias Tee Insertion Loss (Typical, Shunt Configuration)

**Coilcraft 4310LC-220 (22 µH, DC–6 GHz):**
| Frequency | Insertion Loss | Comments |
|-----------|----------------|----------|
| 100 kHz | ~0.1 dB | Choke blocks DC well |
| 1 MHz | ~0.2 dB | Transitional |
| 10 MHz | ~0.3 dB | RF begins to be attenuated |
| 100 MHz | ~0.7 dB | Strong RF blocking |
| 1 GHz | ~1.5 dB | Approach upper frequency limit |
| 6 GHz | ~2–3 dB | At high-frequency limit |

**Coilcraft BCR-802 (800 nH, DC–40 GHz):**
| Frequency | Insertion Loss | Comments |
|-----------|----------------|----------|
| 100 MHz | <0.3 dB | Low loss, excellent matching |
| 1 GHz | <0.5 dB | Wideband design advantage |
| 10 GHz | ~0.8 dB | Still acceptable |
| 40 GHz | ~1.5–2 dB | Upper limit, design-dependent |

---

## Summary: Key Takeaways

1. **dBm conversions matter**: Know the power at each stage (input source, amplifier gain, attenuator, VNA input limit).

2. **Bias tees are critical**: Use Coilcraft 4310LC for DC–6 GHz, BCR for broadband to 40 GHz.

3. **Output attenuators protect VNA**: Keep input to receiver <+20 dBm for safety margin. 6–10 dB pads are standard.

4. **De-embedding is optional but useful**: If you measure with an attenuator/bias tee, you can extract device-only specs post-measurement using cascade removal.

5. **TIA measurements require S→Z conversion**: Direct S-parameter measurement, convert to Z-parameters, extract Z₂₁ (transimpedance gain in Ω).

6. **Photodiode capacitance dominates TIA bandwidth**: Always simulate with realistic input capacitance (~0.6–1 pF total) when measuring without a photodiode.

7. **Stability is first**: Check for oscillation with spectrum analyzer before connecting to VNA. Use K-factor >1 to verify stability.

8. **Calibration with bias tees in-place is cleanest**: TRL calibration at the bias tee output removes their response from the measurement.

---

**End of Guide**

*For questions or clarifications on any section, refer to the source links provided or consult the VNA user manual for your specific instrument.*

