#include <Instruction.hpp>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

using namespace chip8::instruction;

Instruction::Instruction(uint16_t raw) {
    uint8_t h = (raw & 0xF000) >> 12;
    uint8_t x = (raw & 0x0F00) >> 8;
    uint8_t y = (raw & 0x00F0) >> 4;
    uint8_t l = (raw & 0x000F);
    this->raw = raw;
    this->nnn = raw & 0x0FFF;
    this->nn = raw & 0x00FF;
    this->n = raw & 0x000F;
    this->X = x;
    this->Y = y;

    switch (h) {
    case 0: {
        if (x == 0 && y == 14 && l == 0) {
            this->opp = OPP::DISPLAY_CLEAR;
        } else if (x == 0 && y == 14 && l == 14) {
            this->opp = OPP::FLOW_RETURN;
        } else {
            this->opp = OPP::CALL;
        }
        break;
    }
    case 1: {
        this->opp = OPP::FLOW_GOTO;
        break;
    }
    case 2: {
        this->opp = OPP::FLOW_CALL;
        break;
    }
    case 3: {
        this->opp = OPP::COND_EQ_CONST;
        break;
    }
    case 4: {
        this->opp = OPP::COND_NEQ_CONST;
        break;
    }
    case 5: {
        this->opp = OPP::COND_EQ_REG;
        break;
    }
    case 6: {
        this->opp = OPP::CONST_SET;
        break;
    }
    case 7: {
        this->opp = OPP::CONST_ADD;
        break;
    }
    case 8: {
        switch (l) {
        case 0: {
            this->opp = OPP::ASSIG_REG;
            break;
        }
        case 1: {
            this->opp = OPP::BOP_OR;
            break;
        }
        case 2: {
            this->opp = OPP::BOP_ADD;
            break;
        }
        case 3: {
            this->opp = OPP::BOP_XOR;
            break;
        }
        case 4: {
            this->opp = OPP::MATH_ADD;
            break;
        }
        case 5: {
            this->opp = OPP::MATH_SUB;
            break;
        }
        case 6: {
            this->opp = OPP::BOP_SR;
            break;
        }
        case 7: {
            this->opp = OPP::MATH_RSUB;
            break;
        }
        case 14: {
            this->opp = OPP::BOP_SL;
            break;
        }
        default: {
            this->opp = OPP::UNREACHABLE;
            break;
        }
        }
        break;
    }
    case 9: {
        this->opp = OPP::COND_NEQ_REG;
        break;
    }
    case 10: {
        this->opp = OPP::MEM_SET;
        break;
    }
    case 11: {
        this->opp = OPP::FLOW_PC;
        break;
    }
    case 12: {
        this->opp = OPP::RAND;
        break;
    }
    case 13: {
        this->opp = OPP::DISPLAY_DRAW;
        break;
    }
    case 14: {
        if (y == 9 && l == 14) {
            this->opp = OPP::KEY_EQ;
        } else if (y == 10 && l == 1) {
            this->opp = OPP::KEY_NEQ;
        } else {
            this->opp = OPP::UNREACHABLE;
        }
        break;
    }
    case 15: {
        switch (y << 4 | l) {
        case (0 << 4 | 7): {
            break;
        }
        case (0 << 4 | 10): {
            break;
        }
        case (1 << 4 | 5): {
            break;
        }
        case (1 << 4 | 8): {
            break;
        }
        case (1 << 4 | 14): {
            break;
        }
        case (2 << 4 | 9): {
            break;
        }
        case (3 << 4 | 3): {
            break;
        }
        case (5 << 4 | 5): {
            break;
        }
        case (6 << 4 | 5): {
            break;
        }
        default: {
            this->opp = OPP::UNREACHABLE;
            break;
        }
        }
        break;
    }
    default: {
        this->opp = OPP::UNREACHABLE;
        break;
    }
    }
}

std::string Instruction::to_string() {
    std::stringstream ss;

    ss << "0x" << std::uppercase << std::setfill('0') << std::setw(4)
       << std::hex << this->raw;

    ss << "\t" << (int)this->nnn;
    ss << "\t" << (int)this->nn;
    ss << "\t" << (int)this->n;
    ss << "\t" << (int)this->X;
    ss << "\t" << (int)this->Y;

    return ss.str();
}
