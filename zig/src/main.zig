const std = @import("std");
const rl = @import("raylib");

const w = 800;
const h = 600;
const gravity = rl.Vector2{ .x = 0, .y = 1000 };

const Bob = struct {
    ballPos: rl.Vector2,
    ballVel: rl.Vector2,
    length: i16,

    pub fn simulate(self: *Bob, dt: f32, pivot: *const rl.Vector2) void {
        self.ballVel = rl.math.vector2Add(self.ballVel, rl.math.vector2Scale(gravity, dt));
        const new_pos = rl.math.vector2Add(self.ballPos, rl.math.vector2Scale(self.ballVel, dt));

        var dir = rl.math.vector2Subtract(new_pos, pivot.*);
        dir = rl.math.vector2Normalize(dir);

        const dot = rl.math.vector2DotProduct(self.ballVel, dir);
        const radial = rl.math.vector2Scale(dir, dot);

        self.ballVel = rl.math.vector2Subtract(self.ballVel, radial);
        self.ballPos = rl.math.vector2Add(pivot.*, rl.math.vector2Scale(dir, self.length));
    }
};

pub fn main() !void {
    rl.initWindow(w, h, "Hello World!");
    rl.setTargetFPS(60);
    const pivotPos = rl.Vector2{ .x = w * 0.5, .y = h * 0.25 };

    var bob1 = Bob{ .ballPos = rl.Vector2{ .x = w * 0.5, .y = h * 0.5 }, .ballVel = rl.Vector2{ .x = 100, .y = 0 }, .length = 300 };
    var bob2 = Bob{ .ballPos = rl.Vector2{ .x = w * 0.5, .y = h * 0.5 }, .ballVel = rl.Vector2{ .x = 100, .y = 0 }, .length = 200 };

    while (!rl.windowShouldClose()) {
        const dt = rl.getFrameTime();

        bob1.simulate(dt, &pivotPos);
        bob2.simulate(dt, &(bob1.ballPos));

        rl.beginDrawing();
        rl.clearBackground(rl.getColor(0x181818ff));

        rl.drawLineEx(bob1.ballPos, pivotPos, 12, rl.getColor(0xffffffff));
        rl.drawLineEx(bob1.ballPos, bob2.ballPos, 12, rl.getColor(0xffffffff));
        rl.drawCircleV(bob1.ballPos, 50, rl.getColor(0xff5050ff));
        rl.drawCircleV(pivotPos, 15, rl.getColor(0x5050ffff));

        rl.drawCircleV(bob2.ballPos, 50, rl.getColor(0xff5050ff));

        rl.endDrawing();
    }
}
